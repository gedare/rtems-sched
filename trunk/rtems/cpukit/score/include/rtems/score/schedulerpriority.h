/**
 *  @file  rtems/score/schedulerpriority.h
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

/* Include generic scheduling implementations that rely on the ready queue 
 * implementation to provide scheduling logic.
 */
#include <rtems/score/schedulerqueue.h>

/**
 * This routine initializes the priority scheduler.
 */
void _Scheduler_Initialize_priority( Scheduler_Control *sched );

/**
 * This routine allocates the sched field for a new thread.
 */
void * _Scheduler_Sched_allocate_priority(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread
);

/**
 * This routine udpates the sched field of a thread based on the scheduler 
 * structures and thread state
 */
void _Scheduler_Sched_update_priority(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread
);



#ifndef __RTEMS_APPLICATION__
#include <rtems/score/schedulerpriority.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
