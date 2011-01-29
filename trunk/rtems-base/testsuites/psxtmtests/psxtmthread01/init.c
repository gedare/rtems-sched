/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.1 2010/12/06 16:35:30 joel Exp $
 */

#include <coverhd.h>
#include <tmacros.h>
#include <timesys.h>
#include "test_support.h"

#include <pthread.h>

pthread_t ThreadId;

void *TestThread(
  void *argument
)
{
  return NULL;
}


void benchmark_pthread_create(
  int    iteration,
  void  *argument
)
{
  int status;

  status = pthread_create( &ThreadId, NULL, TestThread, NULL );
  rtems_test_assert( !status );
}

void *POSIX_Init(
  void *argument
)
{
  puts( "\n\n*** POSIX TIME TEST THREAD 01 ***" );

  rtems_time_test_measure_operation(
    "pthread_create",
    benchmark_pthread_create,
    NULL,
    1,
    0
  );

  
  puts( "*** END OF POSIX TIME TEST THREAD 01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS     OPERATION_COUNT + 2
#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
