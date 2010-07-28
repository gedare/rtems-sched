/**
 *  @file  rtems/score/scheduler.h
 *
 *  This include file contains all the constants and structures associated
 *  with the scheduler.
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

#ifndef _RTEMS_SCORE_SCHEDULER_H
#define _RTEMS_SCORE_SCHEDULER_H

/**
 *  @defgroup ScoreScheduler Scheduler Handler
 *
 *  This handler encapsulates functionality related to managing sets of threads
 *  that are ready for execution.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/percpu.h>
#include <rtems/score/priority.h>
#include <rtems/score/prioritybitmap.h>
#include <rtems/score/priorityrbtree.h>
#include <rtems/score/rbtree.h>
#include <rtems/score/readyq.h>

/* 
 * These defines are used to set the scheduler_policy value. The values 
 * must correspond directly with the order of the fields in the scheduler
 * table (Scheduler_Table_t), because the Configuration.scheduler_policy 
 * field is used to index the scheduler table.
 */
#define _Scheduler_USER     (0)
#define _Scheduler_PRIORITY (1)
#define _Scheduler_FIFO     (2)
#define _Scheduler_EDF      (3)

typedef struct Scheduler_Control_struct Scheduler_Control;

/* 
 * TODO: Would it make sense to embed the Scheduler_Control for the scheduler
 * here?  Probably not, if we use per-cpu Scheduler_Control...
 */
/*
 * The Scheduler_Table_t type defines the scheduler initialization table, 
 * which is set up by confdefs.h based on the user's choice of scheduler 
 * policy.
 */
typedef struct {
  void (*sched_init)( Scheduler_Control * );
} Scheduler_Table_t;

extern const Scheduler_Table_t _Scheduler_Table[]; /* declared in confdefs.h */

/**
 * The following Scheduler_Per_thread_xxx structures are used to 
 * hold per-thread data used by the scheduler.  Thread_Control->sched is a 
 * union of pointers, one for each of the following structures.  The
 * sched->xxx field points to an instantion of one of these structures, 
 * which is allocated from the workspace during _Thread_Start.
 */

/**
 * Per-thread data related to the _SCHED_PRI scheduling policy.
 */
typedef struct {
  /** This field points to the Ready FIFO for this thread's priority. */
  Chain_Control *ready_chain;

  /** This field contains precalculated priority map indices. */
  Priority_bit_map_Information    Priority_map;
} Scheduler_priority_Per_thread;

/**
 * Per-thread data related to the _SCHED_FIFO scheduling policy.
 */
typedef struct {
  char nothing; /* it doesn't matter, this is never instantiated. */
} Scheduler_fifo_Per_thread;

/**
 * Per-thread data related to the _SCHED_EDF scheduling policy.
 */
typedef struct {
  /** Point back to this thread. */
  Thread_Control                   *this_thread;

  /** This field contains the thread's deadline information. */
  RBTree_Node                       deadline;

  bool                              periodic;
  unsigned integer                  absolute_deadline;

  /** 
   * This field points to the last node in the ready queue that has 
   * the same deadline (absolute) as this thread.
   */
  Chain_Node                       *last_duplicate;
} Scheduler_edf_Per_thread;


/**
 * function jump table that holds pointers to the functions that 
 * implement specific schedulers.
 */
typedef struct {
  /** Implements the scheduling decision logic (policy). */
  void ( *schedule ) ( Scheduler_Control * );

  /** Voluntarily yields the processor per the scheduling policy. */
  void ( *yield ) ( Scheduler_Control * );

  /** Removes the given thread from scheduling decisions. */
  void ( *block ) ( Scheduler_Control *, Thread_Control * );

  /** Adds the given thread to scheduling decisions. */
  void ( *unblock ) ( Scheduler_Control *, Thread_Control * );

  /** allocates the sched field of the given thread */
  void * ( *sched_allocate ) ( Scheduler_Control *, Thread_Control * );

  /** frees the sched field of the given thread */
  void ( *sched_free ) ( Scheduler_Control *, Thread_Control * );
  
  /** updates the sched field of the given thread */
  void ( *sched_update ) ( Scheduler_Control *, Thread_Control * );
} Scheduler_Operations;

/**
 * This is the structure used to manage the scheduler.
 */
struct Scheduler_Control_struct {

  /* A scheduler defines its own ready queue. */
  Ready_queue_Control ready_queue;

  /** The jump table for scheduler-specific functions */
  Scheduler_Operations s_ops;
};

/* TODO: make this per-cpu? then _Scheduler will be a macro. */
/**
 *  The following points to the structures used to manage the
 *  scheduler.
 */
SCORE_EXTERN Scheduler_Control _Scheduler;


/**
 *  This routine initializes the scheduler to the policy chosen by the user 
 *  through confdefs, or to the priority scheduler with ready chains by
 *  default.
 */
void _Scheduler_Handler_initialization( void );

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/scheduler.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
