/**
 *  @file  rtems/score/readyq.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a ready queue.
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
#define _RTEMS_SCORE_READYQ_H

/**
 *  @defgroup ScoreReadyQ Ready Queue Handler
 *
 *  This handler encapsulates functionality related to managing sets of threads
 *  that are ready for execution.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/rqdata.h>

#include <rtems/score/object.h>
#include <rtems/score/thread.h>


/**
 *  Note: The following declarations are for currently unused functions/types.
 */
typedef void ( *Ready_queue_Flush_callout )(
                  Thread_Control *
             );



/** @brief  Ready queue Initialize
 *
 *  This routine initializes the_ready_queue based on the
 *  discipline indicated in attribute_set.  
 */
void _Ready_queue_Initialize(
  Ready_queue_Control         *the_ready_queue,
  Ready_queue_Disciplines      the_discipline
);

/** @brief  Ready queue Dequeue
 *
 * This function removes the next ready thread from the ready queue.
 */
Thread_Control *_Ready_queue_Dequeue(
  Ready_queue_Control *the_ready_queue
);

/** @brief  Ready queue Enqueue
 *
 *  This routine enqueues the given thread on
 *  the_ready_queue.
 */
void _Ready_queue_Enqueue(
  Ready_queue_Control        *the_ready_queue,
  Thread_Control             *the_thread
);

/*
 *  @brief  _Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. If the 
 *  queueing discipling is priority, then the thread will be the first thread
 *  at it's priority level.
 *  
 */

void _Ready_queue_Enqueue_first(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
);

/**
 *  @brief Ready queue Requeue
 *
 *  This routine is invoked when a thread changes priority and remains
 *  ready.  If the queue is priority ordered,
 *  the_thread is removed from the_ready_queue and reinserted using
 *  its new priority.  This method has no impact on the state of the_thread
 *  or of any timeouts associated with this blocking.
 */
void _Ready_queue_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue Extract
 *
 *  This routine removes the_thread from the_ready_queue
 */
void _Ready_queue_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue First
 *
 *  This function returns a pointer to the "first" thread
 *  on the_ready_queue.  The "first" thread is selected
 *  based on the discipline of the_ready_queue.
 */
Thread_Control *_Ready_queue_First(
  Ready_queue_Control *the_ready_queue
);

/**
 * @brief Ready queue Extract priority
 *
 * This macro wraps the underlying call and hides the requeuing argument.
 */

#define _Ready_queue_Extract_priority( _the_ready_queue, _the_thread ) \
  _Ready_queue_Extract_priority_helper( _the_ready_queue, _the_thread, false )

/** 
 * @brief Ready queue Set ready
 *
 * This function sets the ready pointer of @a the_thread based on the 
 * queuing discipline of @a the_ready_queue.
 */
void _Ready_queue_Set_ready(
  Ready_queue_Control *the_ready_queue,
  Thread_Control *the_thread
);

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/readyq.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
