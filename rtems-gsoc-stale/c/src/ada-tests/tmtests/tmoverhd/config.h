/*  config.h
 *
 *  This include file defines the Configuration Table for this test.
 *
 *  COPYRIGHT (c) 1989-1997.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may in
 *  the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: config.h,v 1.5 2007/04/05 15:23:29 joel Exp $
 */


/* configuration information */

#define CONFIGURE_TMTEST

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER

#define CONFIGURE_MAXIMUM_TASKS              2
#define CONFIGURE_MAXIMUM_SEMAPHORES         1
#define CONFIGURE_TICKS_PER_TIMESLICE        0

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_MAXIMUM_POSIX_THREADS              10
#define CONFIGURE_MAXIMUM_POSIX_KEYS                 10
#define CONFIGURE_MAXIMUM_POSIX_MUTEXES              20
#define CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES  10

#include <rtems/confdefs.h>

/* end of include file */
