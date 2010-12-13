/*  Tasks_Periodic
 *
 *  This routine serves as a test task for the slack stealing scheduler 
 *  implementation.
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

rtems_task Tasks_Periodic(
  rtems_task_argument argument
)
{
  rtems_id          rmid;
  rtems_id          test_rmid;
  int               index;
  int               pass;
  uint32_t          failed;
  rtems_status_code status;

  int start, stop;
  int i, j, k;
  rtems_interrupt_level level;

  rtems_periodic_period_status period_stats;
  Thread_CPU_usage_t period_usage;

  struct timespec start_ts, stop_ts, diff_ts;

  status = rtems_periodic_create( argument, &rmid );
  directive_failed( status, "rtems_periodic_create" );
  put_name( Task_name[ argument ], FALSE );
  printf( "- rtems_periodic_create id = 0x%08" PRIxrtems_id "\n", rmid );

  status = rtems_periodic_ident( argument, &test_rmid );
  directive_failed( status, "rtems_periodic_ident" );
  put_name( Task_name[ argument ], FALSE );
  printf( "- rtems_periodic_ident id = 0x%08" PRIxrtems_id "\n", test_rmid );

  if ( rmid != test_rmid ) {
     printf( "RMID's DO NOT MATCH (0x%" PRIxrtems_id " and 0x%" PRIxrtems_id ")\n", rmid, test_rmid );
     rtems_test_exit( 0 );
  }

  put_name( Task_name[ argument ], FALSE );
  printf( "- (0x%08" PRIxrtems_id ") period %" PRIu32 "\n", rmid, Periods[ argument ] );

  status = rtems_task_wake_after( 2 + Phases[argument] );
  directive_failed( status, "rtems_task_wake_after" );

  while (FOREVER) {
    if (rtems_periodic_period(rmid, Periods[argument])==RTEMS_TIMEOUT)
      printf("P%d - Deadline miss\n", argument);

    rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &start);
    printf("P%d-S ticks:%d\n", argument, start);
    if ( start >= 2*HP_LENGTH ) break; /* stop */
    /* active computing */
    
    _Timespec_From_ticks(1, &diff_ts);
    diff_ts.tv_sec = diff_ts.tv_sec / 4; /* probably 0 anyway */
    diff_ts.tv_nsec = diff_ts.tv_nsec / 4; /* this is now 1/4 of a tick */

    set_timespec_from_us( &stop_ts, Execution_us[argument] );

    /* using periodic statistics */
    while(FOREVER) {
      rtems_periodic_get_status(rmid, &period_stats);
      period_usage = period_stats.executed_since_last_period;

      #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
        _Timespec_Add_to(&period_usage, &diff_ts); /* add 1/4 of a tick */
        if (_Timespec_Equal_to(&period_usage, &stop_ts) ||
            _Timespec_Greater_than(&period_usage, &stop_ts)) break;
      #else
        if (period_usage >= Tick_Count[argument]) break;
      #endif
    }
    rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &stop);
    printf("P%d-F ticks:%d\n", argument, stop);
  }

  /* delete period and SELF */
  status = rtems_periodic_delete( rmid );
  if ( status != RTEMS_SUCCESSFUL ) {
    printf("rtems_periodic_delete failed with status of %d.\n",status);
    rtems_test_exit( 0 );
  }
  fflush(stdout);
  puts( "*** END OF TEST SCHEDULER 5 (EDF) ***" );
  rtems_test_exit( 0 );
}
