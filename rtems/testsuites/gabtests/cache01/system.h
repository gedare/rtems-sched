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

#define busy_wait( microseconds, inst_per_us ) \
  do { \
    register uint32_t         _delay=(microseconds); \
    register uint32_t         _inst=(inst_per_us); \
    register int              _tmp=0; \
    asm volatile( "sub     %0, 6, %0; \
        brz     %2, 2f; \
      0: \
        mov     %0, %1; \
      1: \
        nop; \
        sub     %1, 6, %1; \
        nop; \
        nop; \
        brgz  %1, 1b; \
        nop; \
        dec     %2; \
        nop; \
        nop; \
        brnz    %2, 0b; \
      2: nop " \
      : "=r" (_inst), "=r" (_tmp), "=r" (_delay) \
      : "0" (_inst), "1" (_tmp), "2" (_delay) ); \
  } while (0) 

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 1000


#define CONFIGURE_INIT_TASK_PRIORITY          250
#define CONFIGURE_INIT_TASK_INITIAL_MODES     RTEMS_DEFAULT_MODES
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

//#define CONFIGURE_MEMORY_OVERHEAD           ((NUM_TASKS+1)*32*4/1024 + 1)
#define CONFIGURE_MAXIMUM_SEMAPHORES        2

#include "macros.h"
#define CONFIGURE_MAXIMUM_TASKS               (1+NUM_TASKS)
#define CONFIGURE_MAXIMUM_PERIODS             (1+NUM_PERIODIC_TASKS)
//#define CONFIGURE_SCHEDULER_EDF
#include <rtems/confdefs.h>

#include <rtems/rtems/clock.h>
#include <rtems/score/isr.h>
#include <rtems/rtems/intr.h>

/* global variables */
TEST_EXTERN rtems_id   Task_id[ 1+NUM_TASKS ];     /* array of task ids */
TEST_EXTERN rtems_name Task_name[ 1+NUM_TASKS ];   /* array of task names */
extern rtems_task_priority Priorities[ 1+NUM_TASKS ];
extern uint32_t  Periods[ 1 + NUM_PERIODIC_TASKS ];
extern uint32_t  Phases[1 + NUM_TASKS];
extern uint32_t  Execution_us[1 + NUM_TASKS];

extern uint32_t  Instructions_per_us;
extern uint64_t  tick_start, tick_stop;

extern uint32_t   tasks_completed;
extern uint32_t   deadlines_missed;
extern rtems_id   tasks_complete_sem;
extern rtems_id   final_barrier;

extern uint32_t *shared_array;
#define SHARED_ARRAY_SIZE (1024 * 32 * 10) /* 1KB * num_kb * multiplier */
extern uint32_t cache_line_length;
extern uint32_t cache_num_lines_to_access;
/* end of include file */
