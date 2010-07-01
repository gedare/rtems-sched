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
#include <rtems/score/readyqfifo.h>
#include <rtems/score/wkspace.h>
#include <rtems/config.h>

/*
 *
 *  _Ready_queue_Initialize_fifo
 *
 *  This routine initializes @a the_ready_queue for use as a fifo
 *  ready queue.
 *
 *  Input parameters:
 *    the_ready_queue      - pointer to a readyq header
 *
 *  Output parameters: NONE
 */

void _Ready_queue_Initialize_fifo(
  Ready_queue_Control         *the_ready_queue
)
{
  /* allocate ready queue structures */

  /* initialize ready queue structures */
  _Chain_Initialize_empty( &the_ready_queue->Queues.Fifo );

  /* initialize ready queue operations */
  the_ready_queue->rq_ops.dequeue = &_Ready_queue_Dequeue_fifo;
  the_ready_queue->rq_ops.enqueue = &_Ready_queue_Enqueue_fifo;
  the_ready_queue->rq_ops.enqueue_first = &_Ready_queue_Enqueue_first_fifo;
  the_ready_queue->rq_ops.requeue = &_Ready_queue_Requeue_fifo;
  the_ready_queue->rq_ops.extract = &_Ready_queue_Extract_fifo;
  the_ready_queue->rq_ops.first = &_Ready_queue_First_fifo;
}
