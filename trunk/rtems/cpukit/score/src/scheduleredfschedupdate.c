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
#include <rtems/score/priority.h>
#include <rtems/score/prioritybitmap.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerpriority.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Scheduler_edf_Sched_update
 *
 * Updates the sched field of @a the_thread.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread    - pointer to thread control block
 *
 *  Output parameters: NONE
 */

void _Scheduler_edf_Sched_update (
    Scheduler_Control *the_scheduler,
    Thread_Control    *the_thread
)
{
  Scheduler_edf_Per_thread *sched = the_thread->sched.edf;

  sched->absolute_deadline = the_thread->real_priority;

  /* HACK: all aperiodic tasks must be either priority 254 or 255 (Idle) */
  if ( the_thread->real_priority > 253 ) 
    sched->absolute_deadline = 0;

  sched->this_thread = the_thread;
  sched->last_duplicate = &the_thread->Object.Node;

  /* TODO: do this here? */
  sched->deadline.value = 0;
}
