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
  int               start, stop;

  put_name( Task_name[ argument ], FALSE );

  /* Barrier: tasks will be released by the init function */
  status = rtems_semaphore_obtain( tasks_complete_sem, 
      RTEMS_DEFAULT_OPTIONS, 0 );

  rtems_task_wake_after( Phases[ argument ] ); /* typically 0 */

  /*
  rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &start);
  printf("AT%d-S ticks:%d\n", argument, start);
  */

  /* active computing */
  busy_wait( Execution_us[argument], Instructions_per_us );

  /*
  rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &stop);
  printf("P%d-F ticks:%d\n", argument, stop);
  */
  status = rtems_semaphore_obtain( tasks_complete_sem, 
      RTEMS_DEFAULT_OPTIONS, 0 );
  directive_failed( status, "rtems_semaphore_obtain" );
    tasks_completed++;
  status = rtems_semaphore_release( tasks_complete_sem );
  directive_failed( status, "rtems_semaphore_release" );


  fflush(stdout);

  /* The last task terminates the test */
  status = rtems_semaphore_obtain( tasks_complete_sem, 
      RTEMS_DEFAULT_OPTIONS, 0 );
  directive_failed( status, "rtems_semaphore_obtain" );
    if (NUM_TASKS == tasks_completed) {
      sparc64_read_tick( tick_stop );

      printf("#inst spun: %lu \n", tick_stop - tick_start);
      printf("Time spun: %d us\n", 
          (tick_stop - tick_start) / (Instructions_per_us) );
      printf("OS Ticks spun: %d ticks\n", (tick_stop - tick_start) 
          / (Instructions_per_us) / CONFIGURE_MICROSECONDS_PER_TICK );

      printf("\n\n");
      puts( "*** END OF TEST TICKS ***" );

      rtems_test_exit( 0 );
    }
  status = rtems_semaphore_release( tasks_complete_sem );
  directive_failed( status, "rtems_semaphore_release" );


  /* otherwise delete SELF */
  printf( "Killing task %d", argument);
  status = rtems_task_delete(RTEMS_SELF);
  directive_failed(status, "rtems_task_delete of RTEMS_SELF");
}
