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

/*
 *
 *  _Ready_queue_Dequeue_priority
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

Thread_Control *_Ready_queue_Dequeue_priority(
  Ready_queue_Control *the_ready_queue
)
{
  uint32_t        index;
  Chain_Control *rq;
  Thread_Control *the_thread;

  index = _Priority_Get_highest();
  rq = &the_ready_queue->Queues.Priority[index];
  the_thread = (Thread_Control*) _Chain_First(rq);
  
  if ( _Chain_Has_only_one_node( rq ) ) {
    _Chain_Initialize_empty( rq );
    _Priority_Remove( &the_thread->sched.priority->Priority_map );
  } else
    _Chain_Extract_unprotected( &the_thread->Object.Node );
 
  return 0;

}
