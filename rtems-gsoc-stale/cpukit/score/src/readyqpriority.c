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
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqpriority.h>
#include <rtems/score/wkspace.h>
#include <rtems/config.h>

/*
 *
 *  _Ready_queue_priority_Initialize
 *
 *  This routine initializes @a the_ready_queue for use as a priority-based
 *  ready queue.
 *
 *  Input parameters:
 *    the_ready_queue      - pointer to a readyq header
 *
 *  Output parameters: NONE
 */

void _Ready_queue_priority_Initialize(
  Ready_queue_Control         *the_ready_queue
)
{
  uint32_t index;

  /* allocate ready queue structures */
  the_ready_queue->Queues.Priority = (Chain_Control *) 
    _Workspace_Allocate_or_fatal_error(
      (PRIORITY_MAXIMUM + 1) * sizeof(Chain_Control)
    );

  /* initialize ready queue structures */
  for( index=0; index <= PRIORITY_MAXIMUM; index++)
    _Chain_Initialize_empty( &the_ready_queue->Queues.Priority[index] );

  /* initialize ready queue operations */
  the_ready_queue->rq_ops.enqueue       = &_Ready_queue_priority_Enqueue;
  the_ready_queue->rq_ops.enqueue_first = &_Ready_queue_priority_Enqueue_first;
  the_ready_queue->rq_ops.extract       = &_Ready_queue_priority_Extract;
  the_ready_queue->rq_ops.first         = &_Ready_queue_priority_First;
  the_ready_queue->rq_ops.requeue       = &_Ready_queue_priority_Requeue;
}
