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
#include <rtems/score/rqdata.h>

/*PAGE
 *
 *  _Ready_queue_Requeue
 *
 *  This routine is invoked when a thread changes priority and should be
 *  moved to a different position on the ready queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to a readyq header
 *    the_thread       - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

void _Ready_queue_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{

  /*
   * If queueing by FIFO, there is nothing to do. This only applies to
   * priority blocking discipline.
   */
  if ( the_ready_queue->discipline == READY_QUEUE_DISCIPLINE_PRIORITY ) {
    Ready_queue_Control *tq = the_ready_queue;

    _Ready_queue_Extract_priority_helper( tq, the_thread, true );
    (void) _Ready_queue_Enqueue_priority( tq, the_thread );
  }
}

