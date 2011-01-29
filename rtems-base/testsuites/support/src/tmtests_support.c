/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: tmtests_support.c,v 1.2 2010/06/25 16:59:06 joel Exp $
 */

#include <bsp.h>
#include <rtems/timerdrv.h>
#include "test_support.h"
#include "timesys.h"

extern void benchmark_timer_empty_operation(
  int    iteration,
  void  *argument
);

void rtems_time_test_measure_operation(
  const char               *description,
  rtems_time_test_method_t  operation,
  void                     *argument,
  int                       iterations,
  int                       overhead
)
{
  int  i;
  long loop_overhead;
  int  end_time;

  benchmark_timer_initialize();
    for (i=0 ; i<iterations ; i++ ) {
      benchmark_timer_empty_operation( i, argument );
    }
  loop_overhead = benchmark_timer_read();

  benchmark_timer_initialize();
    for (i=0 ; i<iterations ; i++ ) {
      (*operation)( i, argument );
    }
  end_time = benchmark_timer_read();

  put_time(
    description,
    end_time,
    iterations,
    loop_overhead,
    overhead
  );
}
