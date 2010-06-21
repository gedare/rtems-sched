/*
 *  This file implements an empty function used by the RTEMS Timing Tests
 *  to set a baseline for loop overhead.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: tmtests_empty_function.c,v 1.3 2010/06/21 16:54:17 joel Exp $
 */

#include <rtems.h>

rtems_status_code benchmark_timer_empty_function( void );

rtems_status_code benchmark_timer_empty_function( void )
{
  return RTEMS_SUCCESSFUL;
}

void benchmark_timer_empty_operation(
  int    iteration,
  void  *argument
)
{
}
