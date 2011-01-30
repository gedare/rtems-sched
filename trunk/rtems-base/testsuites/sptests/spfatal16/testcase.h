/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.1 2010/06/22 02:15:42 joel Exp $
 */

/* generate fatal errors in termios.c 
 *    rtems_semaphore_create( rtems_build_name ('T', 'R', 'r', c),...);
 */

#define FATAL_ERROR_TEST_NAME            "16"
#define FATAL_ERROR_DESCRIPTION          "termios sem create #1"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_RTEMS_API
#define FATAL_ERROR_EXPECTED_IS_INTERNAL FALSE
#define FATAL_ERROR_EXPECTED_ERROR       RTEMS_TOO_MANY

#define CONFIGURE_APPLICATION_PREREQUISITE_DRIVERS \
  CONSUME_SEMAPHORE_DRIVERS

void force_error()
{
  /* we will not run this far */
}