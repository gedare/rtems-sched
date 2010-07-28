/**
 *  @file  rtems/score/readyqedf.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a edf-based ready queue.
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

#ifndef _RTEMS_SCORE_READYQEDF_H
#define _RTEMS_SCORE_READYQEDF_H

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

#define EDF_PERIODIC   (0)
#define EDF_APERIODIC  (1)

/** @brief  Ready queue Initialize
 *
 *  This routine initializes @a the_ready_queue for edf-based scheduling.
 */
void _Ready_queue_edf_Initialize(
  Ready_queue_Control         *the_ready_queue
);

/** @brief  Ready queue Enqueue
 *
 *  This routine enqueues @a the_thread on the edf-based
 *  @a the_ready_queue.
 */
void _Ready_queue_edf_Enqueue(
  Ready_queue_Control        *the_ready_queue,
  Thread_Control             *the_thread
);

/** @brief  Ready queue Extract
 *
 *  This routine removes @a the_thread from edf-based @a the_ready_queue
 */
void _Ready_queue_edf_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

/** @brief  Ready queue First
 *
 *  This function returns a pointer to the "first" thread
 *  on the_ready_queue.  For edf-based scheduling, this is 
 *  the ready thread with the earliest deadline.
 */
Thread_Control *_Ready_queue_edf_First(
  Ready_queue_Control *the_ready_queue
);

/*
 *  @brief  _Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. For 
 *  edf-based scheduling the thread will be the first thread
 *  with its deadline.
 *
 *  TODO: is this dead code?
 *  
 */

void _Ready_queue_edf_Enqueue_first(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
);

/**
 *  @brief Ready queue Requeue
 *
 *  This routine is invoked when a thread changes priority and remains
 *  ready.  For edf-based ordering,
 *  the_thread is removed from the_ready_queue and reinserted.  
 *  This method has no impact on the state of the_thread
 *
 */
void _Ready_queue_edf_Requeue(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
