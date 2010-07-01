/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.1 2010/07/01 14:40:14 joel Exp $
 */

#include <tmacros.h>
#include "test_support.h"

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void test_gid(void)
{
  gid_t gid;
  int sc;

  gid = getegid();
  printf( "getegid = %d\n", gid );

  gid = getgid();
  printf( "getgid = %d\n", gid );

  puts( "setgid(5)" );
  sc = setgid(5);
  rtems_test_assert( sc == 0 );

  gid = getegid();
  printf( "getegid = %d\n", gid );

  gid = getgid();
  printf( "getgid = %d\n", gid );

  puts( "setpgid(getpid(), 10) - ENOSYS" );
  sc = setpgid( getpid(), 10 );
  rtems_test_assert( sc == -1 );
  rtems_test_assert( errno == ENOSYS );
}

void test_uid(void)
{
  uid_t uid;
  int sc;

  uid = geteuid();
  printf( "geteuid = %d\n", uid );

  uid = getuid();
  printf( "getuid = %d\n", uid );

  puts( "setuid(5)" );
  sc = setuid(5);
  rtems_test_assert( sc == 0 );

  uid = geteuid();
  printf( "geteuid = %d\n", uid );

  uid = getuid();
  printf( "getuid = %d\n", uid );

}

pid_t __getpid(void);
int issetugid(void);

void test_pid(void)
{
  pid_t pid;
  int   sc;

  pid = getpid();
  printf( "getpid = %d\n", pid );

  pid = __getpid();
  printf( "__getpid = %d\n", pid );

  pid = getppid();
  printf( "getppid = %d\n", pid );

  puts( "setsid - EPERM" );
  pid = setsid();
  rtems_test_assert( pid == -1 );
  rtems_test_assert( errno == EPERM );

  sc = issetugid();
  rtems_test_assert( sc == 0 );
}

rtems_task Init(
  rtems_task_argument argument
)
{
  puts( "\n\n*** TEST ID 01 ***" );

  test_gid();
  puts( "" );

  test_uid();
  puts( "" );

  test_pid();
  puts( "" );

  puts( "*** END OF TEST ID 01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
