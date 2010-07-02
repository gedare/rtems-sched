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
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Scheduler_Initialize_queue
 *
 *  This routine initializes the scheduler for queue-based scheduling, 
 *  which embeds the complexity of decision making in the implementation of 
 *  the queue.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_Initialize_queue(
    Scheduler_Control *the_scheduler
)
{
  the_scheduler->s_ops.schedule           = &_Scheduler_Schedule_queue;
  the_scheduler->s_ops.yield              = &_Scheduler_Yield_queue;
  the_scheduler->s_ops.block              = &_Scheduler_Block_queue;
  the_scheduler->s_ops.unblock            = &_Scheduler_Unblock_queue;
  the_scheduler->s_ops.sched_allocate     = &_Scheduler_Sched_allocate_nothing;
  the_scheduler->s_ops.sched_update       = &_Scheduler_Sched_update_nothing;
 
  _Ready_queue_Initialize(&the_scheduler->ready_queue);
}
