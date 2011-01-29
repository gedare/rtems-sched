/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <rtems.h>
extern "C"
{
#include <tmacros.h>
extern rtems_task Task_8puzzle(rtems_task_argument);
}

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_ZERO_WORKSPACE_AUTOMATICALLY TRUE

#define CONFIGURE_MICROSECONDS_PER_TICK 1000

/* these may come from macros.h if flexible RT background is added. */

#define build_task_name() do { \
Task_name[ 1 ] =  rtems_build_name( 'A', '*', '0', '1' ); \
} while( 0 )

#define  NUM_PERIODIC_TASKS         (0)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_ASTAR_TASKS            (1)
#define  NUM_TASKS (NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS + NUM_ASTAR_TASKS)
extern rtems_task_priority Priorities[1+NUM_TASKS];
/***/

#define CONFIGURE_MAXIMUM_TASKS               (1+NUM_TASKS)
#define CONFIGURE_MAXIMUM_PERIODS             (1+NUM_PERIODIC_TASKS)

#define CONFIGURE_MAXIMUM_SEMAPHORES       5

#define CONFIGURE_INIT_TASK_PRIORITY       1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT_TASK_STACK_SIZE    (RTEMS_MINIMUM_STACK_SIZE * 2)
#define CONFIGURE_EXTRA_TASK_STACKS       RTEMS_MINIMUM_STACK_SIZE

/* Only remove when this macro is removed from confdefs.h. It tests it. */
#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM

#include <rtems/confdefs.h>

/* global variables */
TEST_EXTERN rtems_id   Task_id[ 1+NUM_TASKS ];     /* array of task ids */
TEST_EXTERN rtems_name Task_name[ 1+NUM_TASKS ];   /* array of task names */

/* end of include file */
