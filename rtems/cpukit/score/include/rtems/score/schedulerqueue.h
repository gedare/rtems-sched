/**
 *  @file  rtems/score/schedulerqueue.h
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

#ifndef _RTEMS_SCORE_SCHEDULERQUEUE_H
#define _RTEMS_SCORE_SCHEDULERQUEUE_H

/**
 *  @addtogroup ScoreScheduler
 *
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/scheduler.h>

/* 
 * Generic scheduling implementations that rely on the ready queue 
 * implementation to provide scheduling logic. 
 * Note: There is no "queue" scheduler.
 */

/**
 *  This kernel routine sets the heir thread to be the next ready thread 
 *  on the ready queue.
 */
void _Scheduler_Schedule_queue(
    Scheduler_Control *sched 
);

/**
 *  This routine is invoked when a thread wishes to voluntarily
 *  transfer control of the processor to another thread in the queue.
 */
void _Scheduler_Yield_queue( Scheduler_Control *sched );

/**
 *  This routine removes @a the_thread from the scheduling decision, 
 *  that is, removes it from the ready queue.  It performs
 *  any necessary scheduling operations including the selection of
 *  a new heir thread.
 */
void _Scheduler_Block_queue( 
    Scheduler_Control *sched,
    Thread_Control *the_thread 
);

/**
 *  This routine adds @a the_thread to the scheduling decision, 
 *  that is, adds it to the ready queue and 
 *  updates any appropriate scheduling variables, for example the heir thread.
 */
void _Scheduler_Unblock_queue(
    Scheduler_Control *sched,
    Thread_Control *the_thread 
);


#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
