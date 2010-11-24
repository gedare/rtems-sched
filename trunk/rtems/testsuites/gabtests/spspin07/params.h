/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 2,0.069,0 -T 2,0.045,0 -T 3,0.015,0 -T 4,0.075,0 -T 5,0.027,0 -T 6,0.038,0 -T 6,0.047,0 -T 8,0.010,0 -T 9,0.073,0 -T 16,0.041,0 -T 19,0.063,0 -T 21,0.039,0 -T 23,0.067,0 -T 23,0.066,0 -T 39,0.008,0 -T 40,0.015,0 -T 41,0.066,0 -T 43,0.116,0 -T 49,0.099,0 -T 50,0.024,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (50)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 2, 2, 3, 4, 5, 6, 6, 8, 9, 16, 19, 21, 23, 23, 39, 40, 41, 43, 49, 50 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 2, 2, 3, 4, 5, 6, 6, 8, 9, 16, 19, 21, 23, 23, 39, 40, 41, 43, 49, 50 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             2*0.069*CONFIGURE_MICROSECONDS_PER_TICK,
                                             2*0.045*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*0.075*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             6*0.038*CONFIGURE_MICROSECONDS_PER_TICK,
                                             6*0.047*CONFIGURE_MICROSECONDS_PER_TICK,
                                             8*0.01*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.073*CONFIGURE_MICROSECONDS_PER_TICK,
                                             16*0.041*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.063*CONFIGURE_MICROSECONDS_PER_TICK,
                                             21*0.039*CONFIGURE_MICROSECONDS_PER_TICK,
                                             23*0.067*CONFIGURE_MICROSECONDS_PER_TICK,
                                             23*0.066*CONFIGURE_MICROSECONDS_PER_TICK,
                                             39*0.008*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             41*0.066*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.116*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.099*CONFIGURE_MICROSECONDS_PER_TICK,
                                             50*0.024*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

uint32_t  Phases[1+NUM_TASKS]           = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#define build_task_name() do { \
Task_name[ 1 ] =  rtems_build_name( 'P', 'T', '0', '1' );\
Task_name[ 2 ] =  rtems_build_name( 'P', 'T', '0', '2' );\
Task_name[ 3 ] =  rtems_build_name( 'P', 'T', '0', '3' );\
Task_name[ 4 ] =  rtems_build_name( 'P', 'T', '0', '4' );\
Task_name[ 5 ] =  rtems_build_name( 'P', 'T', '0', '5' );\
Task_name[ 6 ] =  rtems_build_name( 'P', 'T', '0', '6' );\
Task_name[ 7 ] =  rtems_build_name( 'P', 'T', '0', '7' );\
Task_name[ 8 ] =  rtems_build_name( 'P', 'T', '0', '8' );\
Task_name[ 9 ] =  rtems_build_name( 'P', 'T', '0', '9' );\
Task_name[ 10 ] =  rtems_build_name( 'P', 'T', '1', '0' );\
Task_name[ 11 ] =  rtems_build_name( 'P', 'T', '1', '1' );\
Task_name[ 12 ] =  rtems_build_name( 'P', 'T', '1', '2' );\
Task_name[ 13 ] =  rtems_build_name( 'P', 'T', '1', '3' );\
Task_name[ 14 ] =  rtems_build_name( 'P', 'T', '1', '4' );\
Task_name[ 15 ] =  rtems_build_name( 'P', 'T', '1', '5' );\
Task_name[ 16 ] =  rtems_build_name( 'P', 'T', '1', '6' );\
Task_name[ 17 ] =  rtems_build_name( 'P', 'T', '1', '7' );\
Task_name[ 18 ] =  rtems_build_name( 'P', 'T', '1', '8' );\
Task_name[ 19 ] =  rtems_build_name( 'P', 'T', '1', '9' );\
Task_name[ 20 ] =  rtems_build_name( 'P', 'T', '2', '0' );\
} while(0)

#endif
