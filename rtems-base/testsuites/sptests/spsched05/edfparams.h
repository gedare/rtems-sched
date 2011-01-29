/* edfparams.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 3,1,0 -T 4,1,0 -T 5,1,0 -T 7,1,0 -A 1,100,7 -A 100,5,4
*/

#ifndef __EDFPARAMS_H_
#define __EDFPARAMS_H_

#define  JOBS_PER_HP                (389)
#define  HP_LENGTH                  (420)
#define  NUM_PERIODIC_TASKS         (4)
#define  NUM_APERIODIC_TASKS        (2)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )

uint32_t  jobs_per_hyperperiod      = JOBS_PER_HP;
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 3, 4, 5, 7, 254, 254 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 3, 4, 5, 7 };
uint32_t  Periods_us[1+NUM_PERIODIC_TASKS] = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*CONFIGURE_MICROSECONDS_PER_TICK,
                                             7*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

uint32_t  Tick_Count[1+NUM_TASKS]           = { 0, 1, 1, 1, 1, 100, 5 };
uint32_t  Execution[1+NUM_TASKS]           = { 0, 1, 1, 1, 1, 100, 5 };
uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*CONFIGURE_MICROSECONDS_PER_TICK,
                                             100*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

uint32_t  Phases[1+NUM_TASKS]           = { 0, 0, 0, 0, 0, 7, 4 };
uint32_t  Phases_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             7*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

#define build_task_name() do { \
Task_name[ 1 ] =  rtems_build_name( 'P', 'T', '1', ' ' );\
Task_name[ 2 ] =  rtems_build_name( 'P', 'T', '2', ' ' );\
Task_name[ 3 ] =  rtems_build_name( 'P', 'T', '3', ' ' );\
Task_name[ 4 ] =  rtems_build_name( 'P', 'T', '4', ' ' );\
Task_name[ 5 ] =  rtems_build_name( 'A', 'T', '5', ' ' );\
Task_name[ 6 ] =  rtems_build_name( 'A', 'T', '6', ' ' );\
} while(0)

#endif
