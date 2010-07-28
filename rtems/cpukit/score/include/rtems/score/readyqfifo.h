/**
 *  @file  rtems/score/readyqfifo.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a FIFO ready queue.
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

#ifndef _RTEMS_SCORE_READYQFIFO_H
#define _RTEMS_SCORE_READYQFIFO_H

/**
 *  @addtogroup ScoreReadyQ
 *
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/readyq.h>
#include <rtems/score/thread.h>

/** @brief  Ready queue Initialize
 *
 *  This routine initializes @a the_ready_queue for fifo-based scheduling.
 */
void _Ready_queue_fifo_Initialize(
  Ready_queue_Control         *the_ready_queue
);

/** @brief  Ready queue Enqueue
 *
 *  This routine enqueues @a the_thread on the fifo-based
 *  @a the_ready_queue.
 */
void _Ready_queue_fifo_Enqueue(
  Ready_queue_Control        *the_ready_queue,
  Thread_Control             *the_thread
);

/*
 *  @brief  _Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. For 
 *  fifo-based scheduling the thread will be the first thread
 *  at its fifo level.
 *  
 */

void _Ready_queue_fifo_Enqueue_first(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
);

/** @brief  Ready queue Extract
 *
 *  This routine removes @a the_thread from fifo-based @a the_ready_queue
 */
void _Ready_queue_fifo_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue First
 *
 *  This function returns a pointer to the "first" thread
 *  on the_ready_queue.  For fifo-based scheduling, this is 
 *  the highest fifo ready thread.
 */
Thread_Control *_Ready_queue_fifo_First(
  Ready_queue_Control *the_ready_queue
);

/**
 *  @brief Ready queue Requeue
 *
 *  This routine is invoked when a thread changes fifo and remains
 *  ready.  For fifo-based ordering,
 *  the_thread is removed from the_ready_queue and reinserted using
 *  its new fifo.  This method has no impact on the state of the_thread
 */
void _Ready_queue_fifo_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
