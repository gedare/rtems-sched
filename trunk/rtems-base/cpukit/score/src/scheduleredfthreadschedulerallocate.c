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
#include <rtems/score/scheduler.h>
#include <rtems/score/scheduleredf.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/wkspace.h>

/*
 *
 *  _Scheduler_edf_Sched_allocate
 *
 * Allocates the sched field of @a the_thread.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread    - pointer to thread control block
 *
 *  Output parameters: NONE
 */

void* _Scheduler_edf_Thread_scheduler_allocate (
    Scheduler_Control *the_scheduler __attribute__((unused)),
    Thread_Control    *the_thread
)
{
  void *sched;

  sched = _Workspace_Allocate( sizeof(Scheduler_edf_Per_thread) );

  the_thread->scheduler.edf = (Scheduler_edf_Per_thread*) sched;

  if ( sched ) {
    the_thread->scheduler.edf->last_duplicate = &the_thread->Object.Node;
    the_thread->scheduler.edf->this_thread    = the_thread;
    the_thread->scheduler.edf->deadline.value = 0;
  }

  return sched;
}
