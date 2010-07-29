/*
 *  Ready Queue Handler
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
#include <rtems/score/chain.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/rbtree.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqedf.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Ready_queue_edf_First
 *
 *  This routines returns a pointer to the first thread on @a the_ready_queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to thread queue
 *
 *  Output parameters:
 *    returns - first thread or NULL
 */

Thread_Control *_Ready_queue_edf_First(
  Ready_queue_Control *the_ready_queue
)
{
  Scheduler_edf_Per_thread *tmp_sched = 0;

  /* if idle is going to be heir, adjust its Deadline and re-queue it. */
  if ( the_ready_queue->Queues.EDF[EDF_PERIODIC].first == 
        &_Thread_Idle->Object.Node ) {
    tmp_sched = _Thread_Idle->sched.edf;
    _Ready_queue_edf_Extract( the_ready_queue, _Thread_Idle ); 

    tmp_sched->deadline.value = tmp_sched->absolute_deadline +
      _Watchdog_Ticks_since_boot;

    _Ready_queue_edf_Enqueue( the_ready_queue, _Thread_Idle );
  }

  /* if idle is still heir, check for aperiodic tasks to run instead */
  if (the_ready_queue->Queues.EDF[EDF_PERIODIC].first == 
      &_Thread_Idle->Object.Node &&
      !_Chain_Is_empty(&the_ready_queue->Queues.EDF[EDF_APERIODIC])) {
    return (Thread_Control *) the_ready_queue->Queues.EDF[EDF_APERIODIC].first;
  } 

  /* otherwise get the first element of the ready queue */
  return (Thread_Control *) the_ready_queue->Queues.EDF[EDF_PERIODIC].first;
}
