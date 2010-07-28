/**
 *  @file  rtems/score/schedulerfifo.h
 *
 *  This include file contains all the constants and structures associated
 *  with the manipulation of threads on a fifo-based ready queue.
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

#ifndef _RTEMS_SCORE_SCHEDULERFIFO_H
#define _RTEMS_SCORE_SCHEDULERFIFO_H

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
 * This routine initializes the fifo scheduler.
 */
void _Scheduler_fifo_Initialize( Scheduler_Control *sched );

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
