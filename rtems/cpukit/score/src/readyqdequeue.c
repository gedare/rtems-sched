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
 *  $Id: readyqdequeue.c,v 1.7 2008/01/22 21:19:18 joel Exp $
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
 *  _Ready_queue_Dequeue
 *
 *  This routine removes the running thread from the specified readyq.  
 *
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *
 *  Output parameters:
 *    returns - thread dequeued or NULL
 *
 *  INTERRUPT LATENCY:
 */

Thread_Control *_Ready_queue_Dequeue(
  Ready_queue_Control *the_ready_queue
)
{
  Thread_Control *(*dequeue_p)( Ready_queue_Control * );
  Thread_Control *the_thread;

  if ( the_ready_queue->discipline == READY_QUEUE_DISCIPLINE_PRIORITY )
    dequeue_p = _Ready_queue_Dequeue_priority;
  else /* must be READY_QUEUE_DISCIPLINE_FIFO */
    dequeue_p = _Ready_queue_Dequeue_fifo;

  the_thread = (*dequeue_p)( the_ready_queue );

#if 0  
  _ISR_Disable( level );
    if ( !the_thread ) {
      sync_state = the_ready_queue->sync_state;
      if ( (sync_state == THREAD_BLOCKING_OPERATION_TIMEOUT) ||
           (sync_state == THREAD_BLOCKING_OPERATION_NOTHING_HAPPENED) ) {
        the_ready_queue->sync_state = THREAD_BLOCKING_OPERATION_SATISFIED;
        the_thread = _Thread_Executing;
      }
    }
  _ISR_Enable( level );
#endif

  return the_thread;
}
