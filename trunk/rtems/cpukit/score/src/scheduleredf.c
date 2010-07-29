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
