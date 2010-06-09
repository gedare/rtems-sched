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

#include <rtems/score/bitfield.h>


/**
 *  Transparent, identically mapped uint32_t-based Priority_Control
 */
RTEMS_INLINE_ROUTINE void _Priority_Set_transparent ( 
    Priority_Control *priority_lhs,
    Priority_Control *priority_rhs
  )
{
  *priority_lhs = *priority_rhs;
}

RTEMS_INLINE_ROUTINE uint32_t _Priority_Get_value_transparent ( 
    Priority_Control priority 
)
{
  return ( priority );
}

RTEMS_INLINE_ROUTINE void _Priority_Set_value_transparent (
    Priority_Control *priority_lhs,
    uint32_t value
  )
{
  *priority_lhs = value;
}


/**
 * Priority_Control external interface
 */
/**
 * @brief Priority set operator
 *
 * Assign @a *priority_lhs = @a *priority_rhs
 */
RTEMS_INLINE_ROUTINE void _Priority_Set ( 
    Priority_Control *priority_lhs,
    Priority_Control *priority_rhs
  )
{
  _Priority_Set_transparent(priority_lhs, priority_rhs);
}

/**
 * @brief Priority Get value operator
 *
 * This method returns the integer priority representation value of 
 * @a _priority, a number between 0 and 255 representing the RTEMS priority.
 */
RTEMS_INLINE_ROUTINE uint32_t _Priority_Get_value ( Priority_Control priority )
{
  return(_Priority_Get_value_transparent( priority ));
}

/**
 * @brief Priority Set value operator
 *
 * This method assigns the integer priority representation value of 
 * @a priority_lhs to be @a value, a number between 0 and 255 representing 
 * the RTEMS priority.
 */
RTEMS_INLINE_ROUTINE void _Priority_Set_value (
    Priority_Control *priority_lhs,
    uint32_t value
  )
{
  _Priority_Set_value_transparent(priority_lhs, value);
}

/**
 *  This routine performs the initialization necessary for this handler.
 */

RTEMS_INLINE_ROUTINE void _Priority_Handler_initialization( void )
{
  int index;

  _Priority_Major_bit_map = 0;
  for ( index=0 ; index <16 ; index++ )
     _Priority_Bit_map[ index ] = 0;
}

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

  return ( _Priority_Get_value(the_priority) <= PRIORITY_MAXIMUM );
}

/**
 *  This function returns the major portion of the_priority.
 */

RTEMS_INLINE_ROUTINE Priority_Bit_map_control   _Priority_Major (
  Priority_Control the_priority
)
{
  return (Priority_Bit_map_control)( _Priority_Get_value(the_priority) / 16 );
}

/**
 *  This function returns the minor portion of the_priority.
 */

RTEMS_INLINE_ROUTINE Priority_Bit_map_control   _Priority_Minor (
  Priority_Control the_priority
)
{
  return (Priority_Bit_map_control)( _Priority_Get_value(the_priority) % 16 );
}

#if ( CPU_USE_GENERIC_BITFIELD_CODE == TRUE )
 
/**
 *  This function returns the mask associated with the major or minor
 *  number passed to it.
 */
 
RTEMS_INLINE_ROUTINE Priority_Bit_map_control   _Priority_Mask (
  uint32_t   bit_number
)
{
  return (Priority_Bit_map_control)(0x8000u >> bit_number);
}
 
/**
 *  This function returns the mask bit inverted.
 */
 
RTEMS_INLINE_ROUTINE Priority_Bit_map_control   _Priority_Mask_invert (
  uint32_t   mask
)
{
  return (Priority_Bit_map_control)(~mask);
}

 
/**
 *  This function translates the bit numbers returned by the bit scan
 *  of a priority bit field into something suitable for use as
 *  a major or minor component of a priority.
 */
 
RTEMS_INLINE_ROUTINE uint32_t   _Priority_Bits_index (
  uint32_t   bit_number
)
{
  return bit_number;
}

#endif

/**
 * Priority Queue implemented by bit map
 */

/**
 *  This routine uses the_priority_map to update the priority
 *  bit maps to indicate that a thread has been readied.
 */

RTEMS_INLINE_ROUTINE void _Priority_Add_bit_map (
  Priority_Information *the_priority_map
)
{
  *the_priority_map->minor |= the_priority_map->ready_minor;
  _Priority_Major_bit_map  |= the_priority_map->ready_major;
}

/**
 *  This routine uses the_priority_map to update the priority
 *  bit maps to indicate that a thread has been removed from the
 *  ready state.
 */

RTEMS_INLINE_ROUTINE void _Priority_Remove_bit_map (
  Priority_Information *the_priority_map
)
{
  *the_priority_map->minor &= the_priority_map->block_minor;
  if ( *the_priority_map->minor == 0 )
    _Priority_Major_bit_map &= the_priority_map->block_major;
}

/**
 *  This function returns the priority of the highest priority
 *  ready thread.
 */

RTEMS_INLINE_ROUTINE Priority_Control _Priority_Get_highest_bit_map( void )
{
  Priority_Bit_map_control minor;
  Priority_Bit_map_control major;

  _Bitfield_Find_first_bit( _Priority_Major_bit_map, major );
  _Bitfield_Find_first_bit( _Priority_Bit_map[major], minor );

  return (_Priority_Bits_index( major ) << 4) +
          _Priority_Bits_index( minor );
}

/**
 *  This routine initializes the_priority_map so that it
 *  contains the information necessary to manage a thread
 *  at new_priority.
 */

RTEMS_INLINE_ROUTINE void _Priority_Initialize_information_bit_map(
  Priority_Information *the_priority_map,
  Priority_Control      new_priority
)
{
  Priority_Bit_map_control major;
  Priority_Bit_map_control minor;
  Priority_Bit_map_control mask;

  major = _Priority_Major( _Priority_Get_value(new_priority) );
  minor = _Priority_Minor( _Priority_Get_value(new_priority) );

  the_priority_map->minor =
    &_Priority_Bit_map[ _Priority_Bits_index(major) ];

  mask = _Priority_Mask( major );
  the_priority_map->ready_major = mask;
  /* Add _Priority_Mask_invert to non-generic bitfield then change this code. */
  the_priority_map->block_major = (Priority_Bit_map_control)(~((uint32_t)mask));

  mask = _Priority_Mask( minor );
  the_priority_map->ready_minor = mask;
  /* Add _Priority_Mask_invert to non-generic bitfield then change this code. */
  the_priority_map->block_minor = (Priority_Bit_map_control)(~((uint32_t)mask));
}


/**
 * Priority Queue Interface functions
 *
 * Currently supports the following priority queue implementations:
 *   Bit map
 */
/**
 * @brief Add @a the_priority_map information to the (global) priority queue.
 *
 */
RTEMS_INLINE_ROUTINE void _Priority_Add( 
    Priority_Information *the_priority_map 
)
{
  _Priority_Add_bit_map(the_priority_map);
}

/**
 * @brief Remove @a the_priority information from the (global) priority queue.
 *
 */
RTEMS_INLINE_ROUTINE void _Priority_Remove(
    Priority_Information *the_priority_map
)
{
  _Priority_Remove_bit_map(the_priority_map);
}

/**
 * @brief Get the highest priority in the (global) priority queue. This 
 * corresponds with the priority of the highest priority ready task.
 *
 */
RTEMS_INLINE_ROUTINE Priority_Control _Priority_Get_highest( void )
{
  return ( _Priority_Get_highest_bit_map() );
}

/**
 * @brief Initializes @a the_priority_map so that it can manage a thread at 
 * priority level @a new_priority.
 *
 * This function should be called whenever a thread is assigned a 
 * priority value, in order to set up its metadata about the (global) 
 * priority queue.
 *
 */
RTEMS_INLINE_ROUTINE void _Priority_Initialize_information (
  Priority_Information *the_priority_map,
  Priority_Control      new_priority
) 
{
  _Priority_Initialize_information_bit_map(the_priority_map, new_priority);
}

/**@}*/

#endif
/* end of include file */
