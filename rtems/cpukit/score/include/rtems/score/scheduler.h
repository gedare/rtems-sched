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

#include <rtems/score/object.h>
#include <rtems/score/thread.h>

/**
 * @brief The following defines provide configuration control over the 
 * scheduler implementation.
 */
#define _SCHED_PRI (1)
#define _SCHED_FIFO (2)

/**
 * @brief SCHEDULER_DEFAULT_POLICY defines the default behavior of the 
 * scheduler via confdefs.
 */
#define SCHEDULER_DEFAULT_POLICY _SCHED_PRI

/**
 *  This routine initializes the scheduler.  
 */
bool _Scheduler_Initialize( void );

/**
 *  This routine is invoked when a thread wishes to voluntarily
 *  transfer control of the processor to another thread of equal
 *  or greater priority.
 */
void _Scheduler_Yield( void );

/**
 *  This routine removes @a the_thread from the scheduling decision, 
 *  that is, removes it from the ready queue.  It performs
 *  any necessary scheduling operations including the selection of
 *  a new heir thread.
 */
void _Scheduler_Block(
  Thread_Control *the_thread
);

/**
 *  This routine adds @a the_thread to the scheduling decision, 
 *  that is, adds it to the ready queue.  It performs
 *  any necessary scheduling operations including the selection of
 *  a new heir thread.
 */
void _Scheduler_Unblock(
  Thread_Control *the_thread
);


#ifndef __RTEMS_APPLICATION__
#include <rtems/score/scheduler.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
