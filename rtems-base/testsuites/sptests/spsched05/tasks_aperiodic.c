/*  Tasks_Aperiodic
 *
 *  This routine serves as a test task for the slack stealing scheduler 
 *  implementation. This is for aperiodic task execution.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include "system.h"

rtems_task Tasks_Aperiodic(
  rtems_task_argument argument
)
{
  int               index;
  rtems_status_code status;

  int start, stop;
  rtems_interrupt_level level;

  struct timespec start_ts, stop_ts, diff_ts;
  Thread_CPU_usage_t initial_usage;
  Thread_CPU_usage_t used;
  Thread_CPU_usage_t thread_usage;

  put_name( Task_name[ argument ], FALSE );

  status = rtems_task_wake_after( 2 + Phases[argument] );
  directive_failed( status, "rtems_task_wake_after" );

  rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &start);
  printf("AT%d-S ticks:%d\n", argument, start);
  /* active computing */

  _Timespec_From_ticks(1, &diff_ts);
  diff_ts.tv_sec = diff_ts.tv_sec / 4; /* probably 0 anyway */
  diff_ts.tv_nsec = diff_ts.tv_nsec / 4; /* this is now 1/4 of a tick */

  set_timespec_from_us( &stop_ts, Execution_us[argument] );
  
  initial_usage = _Thread_Executing->cpu_time_used;

  while(FOREVER) { 
    used = _Thread_Executing->cpu_time_used;

#ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    Thread_CPU_usage_t ran;
    Timestamp_Control        uptime;
  

    _TOD_Get_uptime( &uptime );
    /* ran = time since last context switch */
    _Timestamp_Subtract(
      &_Thread_Time_of_last_context_switch, &uptime, &ran
    );

    /* used += ran */
    _Timestamp_Add_to( &used, &ran );

    /* thread_usage = used - initial cpu usage */
    _Timestamp_Subtract(
        &initial_usage,
        &used,
        &thread_usage
     );

    _Timespec_Add_to(&thread_usage, &diff_ts); /* add 1/4 of a tick */
    if (_Timespec_Equal_to(&thread_usage, &stop_ts) ||
        _Timespec_Greater_than(&thread_usage, &stop_ts)) break;
#else
    used = _Thread_Executing->cpu_time_used;
    
    if (used - initial_usage >= Tick_Count[argument]) break;
#endif
  }
  rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &stop);
  printf("P%d-F ticks:%d\n", argument, stop);

  /* delete SELF */
  fflush(stdout);
  printf( "Killing task %d", argument);
  status = rtems_task_delete(RTEMS_SELF);
  directive_failed(status, "rtems_task_delete of RTEMS_SELF");
}
