/**
 * @file
 *
 * @ingroup Score
 *
 * @brief Basic definitions.
 */

/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Copyright (c) 2010 embedded brains GmbH.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: basedefs.h,v 1.1 2010/07/16 08:31:33 sh Exp $
 */

#ifndef _RTEMS_BASEDEFS_H
#define _RTEMS_BASEDEFS_H

#include <rtems/score/cpuopts.h>

#ifndef ASM
  #include <stddef.h>
  #include <stdbool.h>
  #include <stdint.h>
#endif

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#if TRUE == FALSE
  #error "TRUE equals FALSE"
#endif

/**
 *  The following ensures that all data is declared in the space
 *  of the initialization routine for either the Initialization Manager
 *  or the initialization file for the appropriate API.  It is
 *  referenced as "external" in every other file.
 */
#ifdef SCORE_INIT
#undef  SCORE_EXTERN
#define SCORE_EXTERN
#else
#undef  SCORE_EXTERN
#define SCORE_EXTERN  extern
#endif

/**
 *  The following ensures that all data is declared in the space
 *  of the initialization routine for either the Initialization Manager
 *  or the initialization file for the appropriate API.  It is
 *  referenced as "external" in every other file.
 */
#ifdef SAPI_INIT
#undef  SAPI_EXTERN
#define SAPI_EXTERN
#else
#undef  SAPI_EXTERN
#define SAPI_EXTERN  extern
#endif

/**
 *  The following ensures that all data is declared in the space
 *  of the initialization routine for either the Initialization Manager
 *  or the initialization file for the appropriate API.  It is
 *  referenced as "external" in every other file.
 */
#ifdef RTEMS_API_INIT
#undef  RTEMS_EXTERN
#define RTEMS_EXTERN
#else
#undef  RTEMS_EXTERN
#define RTEMS_EXTERN  extern
#endif

/**
 *  The following ensures that all data is declared in the space
 *  of the initialization routine for either the Initialization Manager
 *  or the initialization file for the appropriate API.  It is
 *  referenced as "external" in every other file.
 */
#ifdef POSIX_API_INIT
#undef  POSIX_EXTERN
#define POSIX_EXTERN
#else
#undef  POSIX_EXTERN
#define POSIX_EXTERN  extern
#endif

/**
 *  The following (in conjunction with compiler arguments) are used
 *  to choose between the use of static inline functions and macro
 *  functions.   The static inline implementation allows better
 *  type checking with no cost in code size or execution speed.
 */
#ifdef __GNUC__
#  define RTEMS_INLINE_ROUTINE static __inline__
#else
#  define RTEMS_INLINE_ROUTINE static inline
#endif

/**
 *  The following macro is a compiler specific way to ensure that memory
 *  writes are not reordered around certian points.  This specifically can
 *  impact interrupt disable and thread dispatching critical sections.
 */
#ifdef __GNUC__
  #define RTEMS_COMPILER_MEMORY_BARRIER() asm volatile("" ::: "memory")
#else
  #define RTEMS_COMPILER_MEMORY_BARRIER()
#endif

/**
 *  The following macro is a compiler specific way to indicate that
 *  the method will NOT return to the caller.  This can assist the
 *  compiler in code generation and avoid unreachable paths.  This
 *  can impact the code generated following calls to
 *  rtems_fatal_error_occurred and _Internal_error_Occurred.
 */
#ifdef __GNUC__
  #define RTEMS_COMPILER_NO_RETURN_ATTRIBUTE \
      __attribute__ ((noreturn))
#else
  #define RTEMS_COMPILER_NO_RETURN_ATTRIBUTE
#endif

/**
 *  Instructs the compiler to issue a warning whenever a variable or function
 *  with this attribute will be used.
 */
#ifdef __GNUC__
  #define RTEMS_COMPILER_DEPRECATED_ATTRIBUTE \
     __attribute__ ((deprecated))
#else
  #define RTEMS_COMPILER_DEPRECATED_ATTRIBUTE
#endif

#ifndef ASM
  #ifdef RTEMS_DEPRECATED_TYPES
    typedef bool boolean;
    typedef float single_precision;
    typedef double double_precision;
  #endif

  /**
   * XXX: Eventually proc_ptr needs to disappear!!!
   */
  typedef void * proc_ptr;
#endif

#endif /* _RTEMS_BASEDEFS_H */
