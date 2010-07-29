/**
 *  @file  rtems/score/readyq.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a ready queue.
 */

/*
 *  Copyright (c) 2010 Gedare Bloom.
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
#include <rtems/score/rbtree.h>

typedef struct Ready_queue_edf_Control_struct Ready_queue_edf_Control;
typedef struct Ready_queue_Control_struct Ready_queue_Control;

/**
 * function jump table that holds pointers to the functions that 
 * implement the ready queue structure-specific code
 */
typedef struct {
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
   * Removes a thread from the ready queue.
   */
  void ( *extract )( Ready_queue_Control *, Thread_Control * );

  /*
   * Returns a pointer to the first (head) thread on the ready queue.
   */
  Thread_Control * ( *first )( Ready_queue_Control * );

  /*
   * Removes and reinserts a thread on the ready queue.
   */
  void ( *requeue )( Ready_queue_Control *, Thread_Control * );

} Ready_queue_Operations;

/**
 *  This is the structure used to manage sets of tasks which are ready to 
 *  use the CPU.
 */
struct Ready_queue_Control_struct {
  /** 
   *  This union contains the pointer to the data structure used to manage 
   *  the ready set of tasks. The pointer varies based upon the type of 
   *  ready queue required by the scheduler.
   */
  union {
    /** 
     * This is the set of lists (an array of Chain_Control) for 
     * priority scheduling. 
     */
    Chain_Control            *Priority;

    /** This points to the Chain_Control for a simple FIFO list. */
    Chain_Control            *Fifo;

    Ready_queue_edf_Control  *EDF;
  } Queues;

  /** The jump table for ready queue structure-specific functions */
  Ready_queue_Operations rq_ops;
};

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/readyq.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
