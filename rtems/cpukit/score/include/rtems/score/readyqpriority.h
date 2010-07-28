/**
 *  @file  rtems/score/readyqpriority.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a priority-based ready queue.
 */

/*
 *  COPYRIGHT (c) 2010.
 *  Gedare Bloom
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_READYQPRIORITY_H
#define _RTEMS_SCORE_READYQPRIORITY_H

/**
 *  @addtogroup ScoreReadyQ
 *
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/priority.h>
#include <rtems/score/readyq.h>
#include <rtems/score/thread.h>

/** @brief  Ready queue Initialize
 *
 *  This routine initializes @a the_ready_queue for priority-based scheduling.
 */
void _Ready_queue_priority_Initialize(
  Ready_queue_Control         *the_ready_queue
);

/** @brief  Ready queue Dequeue
 *
 * This function removes the next ready thread from the priority-based 
 * @a the_ready_queue.
 */
Thread_Control *_Ready_queue_priority_Dequeue(
  Ready_queue_Control *the_ready_queue
);

/** @brief  Ready queue Enqueue
 *
 *  This routine enqueues @a the_thread on the priority-based
 *  @a the_ready_queue.
 */
void _Ready_queue_priority_Enqueue(
  Ready_queue_Control        *the_ready_queue,
  Thread_Control             *the_thread
);

/*
 *  @brief  _Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. For 
 *  priority-based scheduling the thread will be the first thread
 *  at its priority level.
 *  
 */

void _Ready_queue_priority_Enqueue_first(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
);

/**
 *  @brief Ready queue Requeue
 *
 *  This routine is invoked when a thread changes priority and remains
 *  ready.  For priority-based ordering,
 *  the_thread is removed from the_ready_queue and reinserted using
 *  its new priority.  This method has no impact on the state of the_thread
 */
void _Ready_queue_priority_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue Extract
 *
 *  This routine removes @a the_thread from priority-based @a the_ready_queue
 */
void _Ready_queue_priority_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue First
 *
 *  This function returns a pointer to the "first" thread
 *  on the_ready_queue.  For priority-based scheduling, this is 
 *  the highest priority ready thread.
 */
Thread_Control *_Ready_queue_priority_First(
  Ready_queue_Control *the_ready_queue
);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
