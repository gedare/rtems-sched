/**
 *  @file  rtems/score/scheduleredf.h
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

#ifndef _RTEMS_SCORE_SCHEDULEREDF_H
#define _RTEMS_SCORE_SCHEDULEREDF_H

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

/* 
 * TODO: This should only be instantiated if using the rbtree handler.
 */

SCORE_EXTERN RBTree_Control _Ready_queue_edf_RBTree;


/**
 * This routine initializes the edf scheduler.
 */
void _Scheduler_edf_Initialize( Scheduler_Control *sched );

/**
 * This routine allocates the sched field for a new thread.
 */
void * _Scheduler_edf_Sched_allocate(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread
);

/**
 * This routine frees the sched field 
 */
void _Scheduler_edf_Sched_free(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread
);

/**
 * This routine udpates the sched field of a thread based on the scheduler 
 * structures and thread state
 */
void _Scheduler_edf_Sched_update(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread
);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
