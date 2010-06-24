/** 
 *  @file  rtems/score/scheduler.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of the scheduler.
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
# error "Never use <rtems/score/scheduler.inl> directly; include <rtems/score/scheduler.h> instead."
#endif

#ifndef _RTEMS_SCORE_SCHEDULER_INL
#define _RTEMS_SCORE_SCHEDULER_INL

#include <rtems/score/thread.h>

/**
 *  @addtogroup ScoreScheduler
 * @{
 */

/**
 *  This kernel routine sets the heir thread to be the highest priority
 *  ready thread.  This implements the scheduling decision logic. It does 
 *  NOT dispatch.
 */

RTEMS_INLINE_ROUTINE void _Scheduler_Schedule( void )
{
  _Thread_Heir = _Ready_queue_First(&_Thread_Ready_queue);
}


/**@}*/

#endif
/* end of include file */
