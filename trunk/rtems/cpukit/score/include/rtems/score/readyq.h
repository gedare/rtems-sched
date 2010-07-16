/**
 *  @file  rtems/score/readyq.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a ready queue.
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

#include <rtems/score/percpu.h>
#include <rtems/score/chain.h>

typedef struct Ready_queue_Control_struct Ready_queue_Control;

/**
 * function jump table that holds pointers to the functions that 
 * implement the ready queue structure-specific code
 */
typedef struct {
  /*
   * removes the next ready thread from the ready queue.
   */
  Thread_Control * ( *dequeue )( Ready_queue_Control * );

  /*
   * enqueues the given thread on the ready queue.
   */
  void ( *enqueue )( Ready_queue_Control *, Thread_Control * );

  /*
   * enqueues the given thread at the head of the ready queue, respecting 
   * the scheduling policy. e.g. for priority-based scheduling the thread
   * will be the first thread at its priority level.
   */
  void ( *enqueue_first )( Ready_queue_Control *, Thread_Control * );

  /*
   * Removes and reinserts a thread on the ready queue.
   */
  void ( *requeue )( Ready_queue_Control *, Thread_Control * );

  /*
   * Removes a thread from the ready queue.
   */
  void ( *extract )( Ready_queue_Control *, Thread_Control * );

  /*
   * Returns a pointer to the first (head) thread on the ready queue.
   */
  Thread_Control * ( *first )( Ready_queue_Control * );
} Ready_queue_Operations;

/**
 *  This is the structure used to manage sets of tasks which are ready to 
 *  use the CPU.
 */
struct Ready_queue_Control_struct {
  /** 
   *  This union contains the data structures used to manage the ready
   *  set of tasks which varies based upon the type of ready queue required
   *  by the scheduler.
   */
  union {
    /** This is for a simple FIFO list. */
    Chain_Control Fifo;

    /** This is the set of lists for priority scheduling. */
    Chain_Control *Priority;
  } Queues;

  /** The jump table for ready queue structure-specific functions */
  Ready_queue_Operations rq_ops;
};

#ifndef __RTEMS_APPLICATION__

/*RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_First(
      Ready_queue_Control *the_ready_queue
    );*/
#include <rtems/score/readyq.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
