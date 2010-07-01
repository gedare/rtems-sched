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
#include <rtems/score/wkspace.h>

/*
 *
 *  _Scheduler_Sched_allocate_priority
 *
 * Allocates the sched field of @a the_thread.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread    - pointer to thread control block
 *
 *  Output parameters: NONE
 */

void* _Scheduler_Sched_allocate_priority (
    Scheduler_Control *the_scheduler,
    Thread_Control    *the_thread
)
{
  void *sched;

  sched = _Workspace_Allocate( sizeof(Scheduler_Per_thread_priority) );

  the_thread->sched->priority = (Scheduler_Per_thread_priority*) sched;

  return sched;
}
