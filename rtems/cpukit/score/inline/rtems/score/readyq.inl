/** 
 *  @file  rtems/score/readyq.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of ready queues.
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_READYQ_H
# error "Never use <rtems/score/readyq.inl> directly; include <rtems/score/readyq.h> instead."
#endif

#ifndef _RTEMS_SCORE_READYQ_INL
#define _RTEMS_SCORE_READYQ_INL

#include <rtems/score/scheduler.h>

/**
 *  @addtogroup ScoreReadyQ
 * @{
 */


/** @brief  Ready queue Dequeue
 *
 * This function removes the next ready thread from the ready queue.
 */
RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_Dequeue(
  Ready_queue_Control *the_ready_queue
)
{
  return ( the_ready_queue->rq_ops.dequeue( the_ready_queue ) );
}

/** @brief  Ready queue Enqueue
 *
 *  This routine enqueues the given thread on
 *  the_ready_queue.
 */
RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue(
  Ready_queue_Control        *the_ready_queue,
  Thread_Control             *the_thread
)
{
  the_ready_queue->rq_ops.enqueue( the_ready_queue, the_thread );
}

/*
 *  @brief  _Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. If the 
 *  queueing discipling is priority, then the thread will be the first thread
 *  at its priority level.
 *  
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue_first(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  the_ready_queue->rq_ops.enqueue_first( the_ready_queue, the_thread );
}


/**
 *  @brief Ready queue Requeue
 *
 *  This routine is invoked when a thread changes priority and remains
 *  ready.  If the queue is priority ordered,
 *  the_thread is removed from the_ready_queue and reinserted using
 *  its new priority.  This method has no impact on the state of the_thread
 *  or of any timeouts associated with this blocking.
 */
RTEMS_INLINE_ROUTINE void _Ready_queue_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  the_ready_queue->rq_ops.requeue( the_ready_queue, the_thread );
}


/** @brief  Ready queue Extract
 *
 *  This routine removes the_thread from the_ready_queue
 */
RTEMS_INLINE_ROUTINE void _Ready_queue_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  the_ready_queue->rq_ops.extract( the_ready_queue, the_thread );
}


/** @brief  Ready queue First
 *
 *  This function returns a pointer to the "first" thread
 *  on the_ready_queue.  The "first" thread is selected
 *  based on the discipline of the_ready_queue.
 */
RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_First(
  Ready_queue_Control *the_ready_queue
)
{
 return ( the_ready_queue->rq_ops.first( the_ready_queue ) );
}


/** 
 * @brief Ready queue Set ready
 *
 * This function sets the ready pointer of @a the_thread based on the 
 * queuing discipline of @a the_ready_queue.
 */
RTEMS_INLINE_ROUTINE void _Ready_queue_Set_ready(
  Ready_queue_Control *the_ready_queue,
  Thread_Control *the_thread
)
{
  the_ready_queue->rq_ops.set_ready( the_ready_queue, the_thread );
}

/**@}*/

#endif
/* end of include file */
