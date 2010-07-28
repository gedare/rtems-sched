/*
 *  Scheduler Handler
 *
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/score/chain.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqfifo.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerfifo.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/**
 * This routine does nothing, and is used as a stub for Sched_allocate
 *
 * Note: returns a non-zero value, or else thread initialize thinks the 
 * allocation failed.
 *
 * The overhead of a function call will still be imposed. :(
 */
static void * _Scheduler_fifo_Sched_allocate( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
  )
{
  return (void*)-1; /* maybe pick an appropriate poison value */
}


/**
 * This routine does nothing, and is used as a stub for Sched_update
 *
 * The overhead of a function call will still be imposed. :(
 */
static void _Scheduler_fifo_Sched_update( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
  )
{

}

/*
 *
 *  _Scheduler_fifo_Initialize
 *
 * Initializes the scheduler for fifo scheduling.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_fifo_Initialize (
    Scheduler_Control *the_scheduler
)
{
  the_scheduler->s_ops.schedule           = &_Scheduler_queue_Schedule;
  the_scheduler->s_ops.yield              = &_Scheduler_queue_Yield;
  the_scheduler->s_ops.block              = &_Scheduler_queue_Block;
  the_scheduler->s_ops.unblock            = &_Scheduler_queue_Unblock;
  the_scheduler->s_ops.sched_allocate     = &_Scheduler_fifo_Sched_allocate;
  the_scheduler->s_ops.sched_free         = &_Scheduler_fifo_Sched_update;
  the_scheduler->s_ops.sched_update       = &_Scheduler_fifo_Sched_update;
 
  _Ready_queue_fifo_Initialize(&the_scheduler->ready_queue);
}
