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
 *  $Id: system.h,v 1.22 2009/10/05 15:01:59 joel Exp $
 */

#include <tmacros.h>

/* functions */

rtems_task Init(
  rtems_task_argument argument
);

rtems_task Tasks_Periodic(
  rtems_task_argument argument
);

rtems_task Tasks_Aperiodic(
  rtems_task_argument argument
);

void set_timespec_from_us( 
    struct timespec *ts, 
    uint32_t time_us 
);

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 100000

#define CONFIGURE_MAXIMUM_TASKS               7
#define CONFIGURE_MAXIMUM_PERIODS             10

#define CONFIGURE_INIT_TASK_PRIORITY          100
#define CONFIGURE_INIT_TASK_INITIAL_MODES     RTEMS_DEFAULT_MODES
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_EXTRA_TASK_STACKS         (6 * 4 * RTEMS_MINIMUM_STACK_SIZE)

#define CONFIGURE_SCHEDULER_EDF

#include <rtems/confdefs.h>

#include <rtems/rtems/clock.h>
#include <rtems/score/isr.h>
#include <rtems/rtems/intr.h>

/* global variables */
#include "edfmacros.h"
TEST_EXTERN rtems_id   Task_id[ 1+NUM_TASKS ];     /* array of task ids */
TEST_EXTERN rtems_name Task_name[ 1+NUM_TASKS ];   /* array of task names */
extern rtems_task_priority Priorities[ 1+NUM_TASKS ];
extern uint32_t  Periods[ 1 + NUM_PERIODIC_TASKS ];
extern uint32_t  Periods_us[1 + NUM_PERIODIC_TASKS ];
extern uint32_t  Phases[1 + NUM_TASKS];
extern uint32_t  Phases_us[1 + NUM_TASKS];
extern uint32_t  Execution[1 + NUM_TASKS];
extern uint32_t  Execution_us[1 + NUM_TASKS];
extern uint32_t  Tick_Count[1 + NUM_TASKS];

/* extern bool _EDF_hack_started; */

/* end of include file */
