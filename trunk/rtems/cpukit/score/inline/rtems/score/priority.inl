/** 
 *  @file  rtems/score/priority.inl
 *
 *  This file contains the static inline implementation of all inlined
 *  routines in the Priority Handler.
 */

/*
 *  COPYRIGHT (c) 1989-2004.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: priority.inl,v 1.25 2009/05/08 04:55:53 ccj Exp $
 */

#ifndef _RTEMS_SCORE_PRIORITY_H
# error "Never use <rtems/score/priority.inl> directly; include <rtems/score/priority.h> instead."
#endif

#ifndef _RTEMS_SCORE_PRIORITY_INL
#define _RTEMS_SCORE_PRIORITY_INL

/**
 *  @addtogroup ScorePriority 
 *  @{
 */

/**
 *  This function returns true if the_priority if valid for a
 *  user task, and false otherwise.
 */

RTEMS_INLINE_ROUTINE bool _Priority_Is_valid (
  Priority_Control the_priority
)
{
  /* 
   *  Since PRIORITY_MINIMUM is 0 and priorities are stored unsigned,
   *  then checking for less than 0 is unnecessary.
   */

  return ( the_priority <= PRIORITY_MAXIMUM );
}



/**@}*/

#endif
/* end of include file */
