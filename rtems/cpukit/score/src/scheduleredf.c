/*
 *  Scheduler Handler -- EDF scheduling
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
#include <rtems/score/readyqedf.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/scheduleredf.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/watchdog.h>

/* TODO: put this somewhere more appropriate. */
void _Scheduler_edf_Release_job(
  Periodic_Control *the_period
)
{
  ISR_Level       level;

  _ISR_Disable( level );
  
  /* if the thread is already in a ready state, need to dequeue it from
   * the ready queue and then re-enqueue it with the new deadline.
   */
  if ( _States_Is_ready( the_period->owner->current_state ) ) {
    _Ready_queue_edf_Extract(&_Scheduler.ready_queue, the_period->owner);

    /* stamp this job with its new deadline */
    the_period->owner->sched.edf->deadline.value 
      = the_period->owner->real_priority + /* TODO: deadline field? */
        _Watchdog_Ticks_since_boot;

    _Ready_queue_edf_Enqueue(&_Scheduler.ready_queue, the_period->owner);
    _Scheduler_Schedule(&_Scheduler);
  } else {
    the_period->owner->sched.edf->deadline.value 
      = the_period->owner->real_priority + /* TODO: deadline field? */
        _Watchdog_Ticks_since_boot;
  }

  if (the_period->owner != _Thread_Heir)
    _Thread_Dispatch_necessary = true;

  _ISR_Enable( level );
}

/*
 *
 *  _Scheduler_edf_Initialize
 *
 * Initializes the scheduler for edf scheduling.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_edf_Initialize (
    Scheduler_Control *the_scheduler
)
{
  the_scheduler->s_ops.schedule           = &_Scheduler_queue_Schedule;
  the_scheduler->s_ops.yield              = &_Scheduler_queue_Yield;
  the_scheduler->s_ops.block              = &_Scheduler_queue_Block;
  the_scheduler->s_ops.unblock            = &_Scheduler_queue_Unblock;
  the_scheduler->s_ops.sched_allocate     = &_Scheduler_edf_Sched_allocate;
  the_scheduler->s_ops.sched_free         = &_Scheduler_edf_Sched_free;
  the_scheduler->s_ops.sched_update       = &_Scheduler_edf_Sched_update;

  _Ready_queue_edf_Initialize( &the_scheduler->ready_queue );
}
