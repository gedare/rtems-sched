/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2010/08/09 14:29:36 joel Exp $
 */

#include <tmacros.h>
#include "test_support.h"
#include <rtems/libio_.h>
#include <rtems/libcsupport.h>

rtems_task task_routine( rtems_task_argument not_used )
{
  int sc = 0;

  puts( "task_routine - setting up a private environment" );

  sc = rtems_libio_set_private_env();
  sleep( 1 );

  rtems_task_delete( RTEMS_SELF );
}

rtems_task Init(
  rtems_task_argument argument
)
{
  int sc = 0;
  bool status = 0;
  void *alloc_ptr = (void *)0;
  rtems_id current_task_id;
  rtems_id task_id;
  rtems_name another_task_name;
  Heap_Information_block  Info;
  
  puts( "\n\n*** TEST USER ENVIRONMENT ROUTINE - 01 ***" );

  puts( "Init - allocating most of heap -- OK" );
  alloc_ptr = malloc( malloc_free_space() - 4 );
  rtems_test_assert( alloc_ptr != NULL );

  puts( "Init - attempt to reset env - expect RTEMS_NO_MEMORY" );
  sc = rtems_libio_set_private_env();
  rtems_test_assert( sc == RTEMS_NO_MEMORY );

  puts( "Init - freeing the allocated memory" );
  free( alloc_ptr );

  puts( "Init - allocating most of workspace memory" );
  status = rtems_workspace_get_information( &Info );
  rtems_test_assert( status == true );
  status = rtems_workspace_allocate( Info.Free.largest - 4, &alloc_ptr );
  rtems_test_assert( status == true );
  
  puts( "Init - attempt to reset env - expect RTEMS_NO_MEMORY" );
  sc = rtems_libio_set_private_env();
  rtems_test_assert( sc == RTEMS_NO_MEMORY );

  puts( "Init - freeing the workspace memory" );
  status = rtems_workspace_free( alloc_ptr );
  rtems_test_assert( status == true );

  puts( "Init - creating a task name and a task -- OK" );

  another_task_name = 
    rtems_build_name( 'T','S','K','D' );

  sc = rtems_task_create( another_task_name,
			  1,
			  RTEMS_MINIMUM_STACK_SIZE * 2,
			  RTEMS_INTERRUPT_LEVEL(31),
			  RTEMS_DEFAULT_ATTRIBUTES,
			  &task_id
			  );

  puts( "Init - starting the task_routine, to set its private environment" );
  status = rtems_task_start( task_id, task_routine, 0);
  rtems_test_assert(status == 0);

  puts( "Init - attempt to share the env with another task -- Expect error" );
  sc = rtems_libio_share_private_env( task_id );
  rtems_test_assert( sc == RTEMS_INVALID_ADDRESS );

  sleep( 1 );

  puts( "Init - attempt to share the env with another task -- OK" );
  sc = rtems_libio_share_private_env( task_id );
  rtems_test_assert( sc == RTEMS_SUCCESSFUL );
  rtems_test_assert( rtems_current_user_env->task_id == task_id );

  puts( "Init - Get current task id" );
  current_task_id = rtems_task_self();

  puts( "Init - Attempt to reset current task's environment" );
  sc = rtems_libio_set_private_env();
  rtems_test_assert( sc == RTEMS_SUCCESSFUL );
  rtems_test_assert( rtems_current_user_env->task_id == current_task_id );
  
  puts( "Init - attempt to share the env with another task -- OK" );
  sc = rtems_libio_share_private_env( task_id );
  rtems_test_assert( sc == RTEMS_SUCCESSFUL );
  rtems_test_assert( rtems_current_user_env->task_id == task_id );

  puts( "Init - attempt to share with self -- OK" );
  sc = rtems_libio_share_private_env( task_id );
  rtems_test_assert( sc == RTEMS_SUCCESSFUL );

  puts( "*** END OF TEST USER ENVIRONMENT ROUTINE - 01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             3
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
