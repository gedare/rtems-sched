/*  Tasks_Periodic
 *
 *  This routine serves as the body of a periodic task 
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
  rtems_status_code status;
  int i=0;
  //int               start, stop;
  uint32_t          periods_executed;
  uint32_t          local_deadlines_missed;
  uint32_t          temp = 0;
  uint32_t          count = 0;
  uint64_t  start_tick, stop_tick;

  /* local variables to partition the shared array by each task */
  uint32_t  *partition_base;
  uint32_t  partition_size;

  status = rtems_rate_monotonic_create( argument, &rmid );
  directive_failed( status, "rtems_rate_monotonic_create" );
/*
  put_name( Task_name[ argument ], FALSE );
  printf( "- rtems_rate_monotonic_create id = 0x%08" PRIxrtems_id "\n", rmid );
*/
  status = rtems_rate_monotonic_ident( argument, &test_rmid );
  directive_failed( status, "rtems_rate_monotonic_ident" );
/*
  put_name( Task_name[ argument ], FALSE );
  printf( "- rtems_rate_monotonic_ident id = 0x%08" PRIxrtems_id "\n", 
      test_rmid );
*/
  if ( rmid != test_rmid ) {
     printf( "RMID's DO NOT MATCH (0x%" PRIxrtems_id " and 0x%" 
         PRIxrtems_id ")\n", rmid, test_rmid );
     rtems_test_exit( 0 );
  }
/*
  put_name( Task_name[ argument ], FALSE );
  printf( "- (0x%08" PRIxrtems_id ") period %" PRIu32 "\n", 
      rmid, Periods[ argument ] );
*/
  /* release all periodic tasks at the same time */
  /* Barrier: tasks will be released by the init function */
  status = rtems_semaphore_obtain( tasks_complete_sem, 
      RTEMS_DEFAULT_OPTIONS, 0 );

  rtems_task_wake_after( Phases[ argument ] ); /* typically 0 */

  periods_executed = 0;
  local_deadlines_missed = 0;

  partition_size = SHARED_ARRAY_SIZE/NUM_TASKS;
  partition_base =  &shared_array[argument*(partition_size/sizeof(uint32_t))];
  /* Periodic Loop */
  while (FOREVER) {
    if (rtems_rate_monotonic_period(rmid, Periods[argument])==RTEMS_TIMEOUT)
      local_deadlines_missed++;
   /* 
    rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &start);
    printf("P%d-S ticks:%d\n", argument, start);
    */

    /*
    rtems_task_wake_after(1);
    */

    /*
    sparc64_read_tick( tick_start );
    */
     
    /* active computing */
//    busy_wait( Execution_us[argument], Instructions_per_us ); 

    /* loop through shared_array by cache_line_length until 
     * done accessing cache_num_lines_to_access. half of accesses 
     * are writes, and half are reads. */
    count = 0;
    for ( i = 0; 
          i < cache_num_lines; 
          i++) 
    {
      if ((argument+i)%2) {
        /* read */
        if(partition_base[ 
                i*(cache_line_length/sizeof(uint32_t)) 
                % partition_size/(sizeof(uint32_t))
             ] == argument)
          temp++;
      }
      else {
        /* write */
        partition_base[
            i*(cache_line_length/sizeof(uint32_t)) 
            % (partition_size/sizeof(uint32_t))
          ] = argument;
      }
    }

    /*
      sparc64_read_tick( tick_stop );
      printf("#inst spun: %lu \n", tick_stop - tick_start);
      printf("Time spun: %d us\n", 
          (tick_stop - tick_start) / (Instructions_per_us) );
    */
    periods_executed++;

    /*
    rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &stop);
    printf("P%d-F ticks:%d\n", argument, stop);
    */

    /* termination condition: based on amount of 'work' completed. */
    if ( periods_executed*Periods[argument] >= 2*MAX_PERIOD ) break; 
  }

  status = rtems_semaphore_obtain( tasks_complete_sem, 
      RTEMS_DEFAULT_OPTIONS, 0 );
  directive_failed( status, "rtems_semaphore_obtain" );
    tasks_completed++;
    deadlines_missed += local_deadlines_missed;

    if ( NUM_TASKS == tasks_completed ) {
      if (deadlines_missed) {
        MAGIC(1);
      }
      MAGIC_BREAKPOINT;
      printf("%d\n", temp); /* so the compiler doesn't DCE */
      rtems_test_exit( 0 );
    }
  status = rtems_semaphore_release( tasks_complete_sem );
  directive_failed( status, "rtems_semaphore_release" );

  /* Should block forever */
  status = rtems_semaphore_obtain( final_barrier, RTEMS_DEFAULT_OPTIONS, 0 );
  directive_failed( status, "rtems_semaphore_obtain" );

  /* Shouldn't reach this */
  printf( "Killing task %d\n", argument);
  status = rtems_task_delete(RTEMS_SELF);
  directive_failed(status, "rtems_task_delete of RTEMS_SELF");
}
