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
  /* when there are periodic jobs to run, schedule them first */
  if ( !_Chain_Is_empty(&the_ready_queue->Queues.EDF->deadline_queue ) )
    return (Thread_Control *) the_ready_queue->Queues.EDF->deadline_queue.first;

  /* otherwise schedule aperiodic jobs as background tasks */

  /* If idle is going to be heir, re-queue it. */
  if ( the_ready_queue->Queues.EDF->fifo_queue.first == 
        &_Thread_Idle->Object.Node ) {
    _Ready_queue_edf_Extract( the_ready_queue, _Thread_Idle ); 
    _Ready_queue_edf_Enqueue( the_ready_queue, _Thread_Idle );
  }

  /* this is the idle thread if there are no other aperiodic jobs */
  return (Thread_Control *) the_ready_queue->Queues.EDF->fifo_queue.first;
}
