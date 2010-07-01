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
#include <rtems/score/schedulerpriority.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Scheduler_Initialize_priority
 *
 * Initializes the scheduler for priority scheduling.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_Initialize_priority (
    Scheduler_Control *the_scheduler
)
{
  _Scheduler_Initialize_queue(the_scheduler);
  the_scheduler->s_ops.sched_allocate    = &_Scheduler_Sched_allocate_priority;
  the_scheduler->s_ops.sched_update      = &_Scheduler_Sched_Update_priority;
}
