/*
 *  Ready Queue Handler -- EDF
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
#include <rtems/score/readyqedf.h>
#include <rtems/score/wkspace.h>
#include <rtems/config.h>

/*
 *
 *  _Ready_queue_edf_Initialize
 *
 *  This routine initializes @a the_ready_queue for use as a priority-based
 *  ready queue.
 *
 *  Input parameters:
 *    the_ready_queue      - pointer to a readyq header
 *
 *  Output parameters: NONE
 */

void _Ready_queue_edf_Initialize(
  Ready_queue_Control         *the_ready_queue
)
{
  /* allocate ready queue structures */
  the_ready_queue->Queues.EDF = (Chain_Control *) 
    _Workspace_Allocate_or_fatal_error( (2) * sizeof(Chain_Control) );

  /* initialize ready queue structures */
  _Chain_Initialize_empty( &the_ready_queue->Queues.EDF[0] );
  _Chain_Initialize_empty( &the_ready_queue->Queues.EDF[1] );

  _RBTree_Initialize_empty( &_Ready_queue_edf_RBTree );

  /* initialize ready queue operations */
  the_ready_queue->rq_ops.enqueue           = &_Ready_queue_edf_Enqueue;
  the_ready_queue->rq_ops.enqueue_first     = &_Ready_queue_edf_Enqueue_first;
  the_ready_queue->rq_ops.extract           = &_Ready_queue_edf_Extract;
  the_ready_queue->rq_ops.first             = &_Ready_queue_edf_First;
  the_ready_queue->rq_ops.requeue           = &_Ready_queue_edf_Requeue;
}
