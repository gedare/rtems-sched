/**
 * @file rtems/score/types.h
 */

/*
 *  This include file contains type definitions pertaining to the Intel
 *  m32r processor family.
 *
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: types.h,v 1.3 2010/07/16 08:40:07 sh Exp $
 */

#ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#include <rtems/score/basedefs.h>

#ifndef ASM

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  This section defines the basic types for this processor.
 */

/** This defines the type for a priority bit map entry. */
typedef uint16_t Priority_Bit_map_control;

/** This defines the return type for an ISR entry point. */
typedef void m32r_isr;

/** This defines the prototype for an ISR entry point. */
typedef m32r_isr ( *m32r_isr_entry )( void );

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
