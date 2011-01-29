/*
 *  Copyright (c) 2010 Gedare Bloom.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#define CONFIGURE_INIT
#include "system.h"

#include "params.h"
#include <bsp.h>
#include <boot/ofw.h>

#define CPU_FREQ (5000000)

static unsigned int get_Frequency(void)
{
	phandle root = ofw_find_device("/");
	unsigned int freq;
	if (ofw_get_property(root, "clock-frequency", &freq, sizeof(freq)) <= 0) {
		printk("Unable to determine frequency, default: 0x%x\n",CPU_FREQ);
		return CPU_FREQ;
	}

	return freq;
}

uint32_t  Instructions_per_us;
uint32_t  tasks_completed;
uint32_t  deadlines_missed;
uint64_t  tick_start, tick_stop;
rtems_id  tasks_complete_sem;
rtems_id  final_barrier;
uint32_t *shared_array;

uint32_t  cache_line_length = 64;
uint32_t  cache_num_lines = 512*(0.1+0.8); /* 512*(portion of cache) */

rtems_task Init(
  rtems_task_argument argument
)
{
  uint32_t          freq; 
  uint32_t          index;
  rtems_status_code status;

  /*
  puts( "\n\n*** TEST SPINNING ***" );
  */

  /* Calculate the frequency and Instructions_per_us */
  freq = get_Frequency( );
  Instructions_per_us = freq / 1000000;

  tasks_completed = 0;
  deadlines_missed = 0;

  if ( Instructions_per_us == 0 ) {
    puts( "error: CPU frequency is too low" );
    rtems_test_exit(0);
  }

  build_task_name();

    status = rtems_semaphore_create(
      rtems_build_name( 'S', 'E', 'M', '0' ),  /* name = SEM0 */
      0,                                       /* locked */
      RTEMS_BINARY_SEMAPHORE | RTEMS_FIFO,     /* mutex w/desired discipline */
      0,                                       /* IGNORED */
      &tasks_complete_sem
    );
  directive_failed( status, "rtems_semaphore_create" );

  status = rtems_semaphore_create(
      rtems_build_name( 'S', 'E', 'M', '1' ),  /* name = SEM1 */
      0,                                       /* locked */
      RTEMS_SIMPLE_BINARY_SEMAPHORE,           /* mutex w/desired discipline */
      0,                                       /* IGNORED */
      &final_barrier
    );
  directive_failed( status, "rtems_semaphore_create" );

  for ( index = 1 ; index <= NUM_TASKS ; index++ ) {
    status = rtems_task_create(
      Task_name[ index ],
      Priorities[ index ],
      RTEMS_MINIMUM_STACK_SIZE,
      RTEMS_DEFAULT_MODES,
      RTEMS_DEFAULT_ATTRIBUTES,
      &Task_id[ index ]
    );
    directive_failed( status, "rtems_task_create loop" );
  }

  shared_array = malloc(SHARED_ARRAY_SIZE); /* 1 KB * num */
  if (!shared_array) {
    puts( "error, unable to allocate from workspace" );
    rtems_test_exit(0);
  }


  tick_start = tick_stop = 0;

  for ( index = 1 ; index <= NUM_PERIODIC_TASKS ; index++ ) {
    status = rtems_task_start( Task_id[ index ], Tasks_Periodic, index );
    directive_failed( status, "rtems_task_start loop" );
  }

  for ( index = NUM_PERIODIC_TASKS+1 ; index <= NUM_TASKS ; index++ ) {
    status = rtems_task_start( Task_id[ index ], Tasks_Aperiodic, index );
    directive_failed( status, "rtems_task_start loop" );
  }
  /*  
  printf("OS Ticks to run: %d ticks\n", MAX_PERIOD * 2 );
  */

  /* sleep while holding semaphore: is 10 ticks enough? */
  rtems_task_wake_after( 10 );

  /* protected by semaphore */
  sparc64_read_tick( tick_start );
  asm volatile("break_start_opal:");

  /* release all of the waiting tasks */
  status = rtems_semaphore_flush( tasks_complete_sem );
  directive_failed( status, "rtems_semaphore_flush" );

  status = rtems_semaphore_release( tasks_complete_sem );
  directive_failed( status, "rtems_semaphore_release" );

  /* Should block forever */
  status = rtems_semaphore_obtain( final_barrier, RTEMS_DEFAULT_OPTIONS, 0 );
  directive_failed( status, "rtems_semaphore_obtain" );

  puts("Init killing self\n");

  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}

/* end of file */
