/** 
 *  @file  rtems/score/periodic.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the Periodic Manager.
 */

/*
 *  Copyright (c) 2010 Gedare Bloom.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_PERIODIC_H
# error "Never use <rtems/score/periodic.inl> directly; include <rtems/score/periodic.h> instead."
#endif

#ifndef _RTEMS_SCORE_PERIODIC_INL
#define _RTEMS_SCORE_PERIODIC_INL

/**
 *  @addtogroup ScorePeriodic
 * @{
 */

/**
 *  @brief Periodic_Allocate
 *
 *  This function allocates a period control block from
 *  the inactive chain of free period control blocks.
 */
RTEMS_INLINE_ROUTINE Periodic_Control *_Periodic_Allocate( void )
{
  return (Periodic_Control *)
    _Objects_Allocate( &_Periodic_Information );
}

/**
 *  @brief Periodic_Free
 *
 *  This routine allocates a period control block from
 *  the inactive chain of free period control blocks.
 */
RTEMS_INLINE_ROUTINE void _Periodic_Free (
  Periodic_Control *the_period
)
{
  _Objects_Free( &_Periodic_Information, &the_period->Object );
}

/**
 *  @brief Periodic_Get
 *
 *  This function maps period IDs to period control blocks.
 *  If ID corresponds to a local period, then it returns
 *  the_period control pointer which maps to ID and location
 *  is set to OBJECTS_LOCAL.  Otherwise, location is set
 *  to OBJECTS_ERROR and the_period is undefined.
 */
RTEMS_INLINE_ROUTINE Periodic_Control *_Periodic_Get (
  Objects_Id         id,
  Objects_Locations *location
)
{
  return (Periodic_Control *)
    _Objects_Get( &_Periodic_Information, id, location );
}

/**
 *  @brief Periodic_Is_active
 *
 *  This function returns TRUE if the_period is in the ACTIVE state,
 *  and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Periodic_Is_active (
  Periodic_Control *the_period
)
{
  return (the_period->state == PERIODIC_ACTIVE);
}

/**
 *  @brief Periodic_Is_inactive
 *
 *  This function returns TRUE if the_period is in the ACTIVE state,
 *  and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Periodic_Is_inactive (
  Periodic_Control *the_period
)
{
  return (the_period->state == PERIODIC_INACTIVE);
}

/**
 *  @brief Periodic_Is_expired
 *
 *  This function returns TRUE if the_period is in the EXPIRED state,
 *  and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Periodic_Is_expired (
  Periodic_Control *the_period
)
{
  return (the_period->state == PERIODIC_EXPIRED);
}

/**
 *  @brief Periodic_Is_null
 *
 *  This function returns TRUE if the_period is NULL and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE bool _Periodic_Is_null (
  Periodic_Control *the_period
)
{
  return (the_period == NULL);
}






/**@}*/

#endif
/* end of include file */
