/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.1 2010/07/09 22:07:11 joel Exp $
 */

#include <bsp.h>
#include <pmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <rtems/score/heap.h>

extern Heap_Control  *RTEMS_Malloc_Heap;

rtems_task Init(
  rtems_task_argument not_used
)
{
  int fd[2] = {0};
  int dummy_fd[2] = {0};
  int status = 0;
  void *alloc_ptr = (void *)0;
  Heap_Information_block Info;

  puts( "*** TEST POSIX PIPE CREATION - 01 ***" );

  puts( "Init - attempt to create pipe -- expect EFAULT" );
  status = pipe( NULL );
  rtems_test_assert( status == -1 );
  rtems_test_assert( errno == EFAULT );

  puts( "Init - create pipe -- OK" );
  status = pipe( fd );
  rtems_test_assert( status == 0 );

  status = close( fd[0] );
  status |= close( fd[1] );
  rtems_test_assert( status == 0 );

  puts( "Init - create pipe -- OK" );
  status = pipe( fd );
  rtems_test_assert( status == 0 );

  status = close( fd[0] );
  status |= close( fd[1] );
  rtems_test_assert( status == 0 );

  _Heap_Get_information(RTEMS_Malloc_Heap, &Info);
  alloc_ptr = malloc(Info.Free.largest-4);

  /* case where mkfifo fails */
  puts( "Init - attempt to create pipe -- expect ENOMEM" );
  status = pipe( fd );
  rtems_test_assert( status == -1 );
  rtems_test_assert( errno == ENOMEM );

  free( alloc_ptr );
  
  dummy_fd[0] = open( "/file01", O_RDONLY | O_CREAT, S_IRWXU );
  rtems_test_assert( dummy_fd[0] != -1 );
  dummy_fd[1] = open( "/file02", O_RDONLY | O_CREAT, S_IRWXU );
  rtems_test_assert( dummy_fd[1] != -1 );

  /* case where fifo_open for read => open fails */
  puts( "Init - create pipe -- expect ENFILE" );
  status = pipe( fd );
  rtems_test_assert( status == -1 );
  rtems_test_assert( errno == ENFILE );

  status = close( dummy_fd[1] );
  status |= unlink( "/file02" );
  rtems_test_assert( status == 0 );

  /* case where fifo_open for write => open fails */
  puts( "Init - create pipe -- expect ENFILE" );
  status = pipe( fd );
  rtems_test_assert( status == -1 );
  rtems_test_assert( errno == ENFILE );

  status = close( dummy_fd[0] );
  status |= unlink( "/file01" );
  rtems_test_assert( status == 0 );

  puts( "*** END OF TEST POSIX PIPE CREATION - 01 ***" );
  rtems_test_exit( 0 );
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5

#define CONFIGURE_MAXIMUM_TASKS 1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_PIPES_ENABLED
#define CONFIGURE_MAXIMUM_PIPES 2

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
/* end of file */
