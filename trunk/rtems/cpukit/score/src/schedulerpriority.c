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
#include <rtems/score/readyqpriority.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerpriority.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/* Instantiate any global variables needed by the priority scheduler */
volatile Priority_bit_map_Control _Priority_Major_bit_map;

Priority_bit_map_Control _Priority_Bit_map[16] CPU_STRUCTURE_ALIGNMENT;


/*
 *
 *  _Scheduler_priority_Initialize
 *
 * Initializes the scheduler for priority scheduling.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_priority_Initialize (
    Scheduler_Control *the_scheduler
)
{
  the_scheduler->s_ops.schedule           = &_Scheduler_queue_Schedule;
  the_scheduler->s_ops.yield              = &_Scheduler_queue_Yield;
  the_scheduler->s_ops.block              = &_Scheduler_queue_Block;
  the_scheduler->s_ops.unblock            = &_Scheduler_queue_Unblock;
  the_scheduler->s_ops.sched_allocate    = &_Scheduler_priority_Sched_allocate;
  the_scheduler->s_ops.sched_free        = &_Scheduler_priority_Sched_free;
  the_scheduler->s_ops.sched_update      = &_Scheduler_priority_Sched_update;

  _Ready_queue_priority_Initialize(&the_scheduler->ready_queue);
  _Priority_bit_map_Handler_initialization();
}
