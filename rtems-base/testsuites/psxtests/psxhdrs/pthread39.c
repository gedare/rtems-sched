/*
 *  This test file is used to verify that the header files associated with
 *  invoking this function are correct.
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pthread39.c,v 1.1 2010/10/04 16:09:44 joel Exp $
 */

#if HAVE_DECL_PTHREAD_ATTR_SETGUARDSIZE
#include <pthread.h>
#include <limits.h>  /* only for PTHREAD_STACK_MIN */

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_setstacksize"
#endif

void test( void );

void test( void )
{
  pthread_attr_t  attribute;
  size_t          size;
  int             result;

  size = PTHREAD_STACK_MIN;

  result = pthread_attr_setguardsize( &attribute, size );
}
#endif
