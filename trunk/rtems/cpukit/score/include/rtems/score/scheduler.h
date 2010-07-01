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
#include <rtems/score/readyq.h>


/** 
 * @brief The following defines provide configuration control over the 
 * scheduler implementation.
 *
 * When adding a new scheduler implementation, give it a unique definition 
 * here so that users can select an arbitrary scheduler for their application.
 * Also add a brief description of the option here.
 *
 * _SCHED_PRI:  
 *  Queue-based scheduling with a priority-map ready queue.
 * 
 * _SCHED_FIFO: 
 *  Queue-based scheduling with a FIFO ready queue.
 *
 */
#define _SCHED_PRI (1)
#define _SCHED_FIFO (2)

/**
 * @brief SCHEDULER_DEFAULT_POLICY defines the default behavior of the 
 * scheduler via confdefs.  The default behavior is the original RTEMS 
 * priority-based scheduling using the priority map ready queue.
 */
#define SCHEDULER_DEFAULT_POLICY _SCHED_PRI


typedef struct Scheduler_Control_struct Scheduler_Control;

/**
 * function jump table that holds pointers to the functions that 
 * implement specific schedulers.
 */
typedef struct {
  /** Implements the scheduling decision logic (policy). */
  void ( *schedule ) ( Scheduler_Control* );

  /** Voluntarily yields the processor per the scheduling policy. */
  void ( *yield ) ( Scheduler_Control* );

  /** Removes the given thread from scheduling decisions. */
  void ( *block ) ( Scheduler_Control*, Thread_Control * );

  /** Adds the given thread to scheduling decisions. */
  void ( *unblock ) ( Scheduler_Control*, Thread_Control * );
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
void _Scheduler_Initialize( void );


#ifndef __RTEMS_APPLICATION__
#include <rtems/score/scheduler.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
