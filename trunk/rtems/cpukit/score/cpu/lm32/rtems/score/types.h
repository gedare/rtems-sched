/**
 * @file rtems/score/types.h
 */

/*
 *  This include file contains type definitions pertaining to the
 *  Lattice lm32 processor family.
 *
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: types.h,v 1.3 2010/07/16 08:39:05 sh Exp $
 *
 *  Jukka Pietarinen <jukka.pietarinen@mrf.fi>, 2008,
 *  Micro-Research Finland Oy
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
typedef uint16_t Priority_bit_map_Control;

/** This defines the return type for an ISR entry point. */
typedef void lm32_isr;

/** This defines the prototype for an ISR entry point. */
typedef lm32_isr ( *lm32_isr_entry )( void );

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
