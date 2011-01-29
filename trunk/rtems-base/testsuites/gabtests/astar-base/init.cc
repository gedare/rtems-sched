/*  Init
 *
 *  This routine is the initialization task for this test program.
 *  It is called from init_exec and has the responsibility for creating
 *  and starting the tasks that make up the test.  If the time of day
 *  clock is required for the test, it should also be set to a known
 *  value by this function.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
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

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdlib.h>

/* Probably get this from params.h */
rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 5 };

/** TODO: add periodic and aperiodic tasks */
rtems_task Init(
  rtems_task_argument argument
)
{
  uint32_t          index;
  rtems_status_code status;

  /* Setup tasks */
  build_task_name();
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
  
  for ( index = NUM_PERIODIC_TASKS+NUM_APERIODIC_TASKS+1 ; 
        index <= NUM_TASKS ; index++ ) {
    status = rtems_task_start( Task_id[ index ], Task_8puzzle, index );
    directive_failed( status, "rtems_task_start loop" );
  }

  asm volatile ("break_start_opal:");
  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}
