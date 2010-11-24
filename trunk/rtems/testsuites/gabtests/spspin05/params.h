/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 1,0.092,0 -T 10,0.038,0 -T 11,0.004,0 -T 13,0.034,0 -T 17,0.067,0 -T 18,0.083,0 -T 19,0.052,0 -T 19,0.065,0 -T 28,0.078,0 -T 32,0.069,0 -T 32,0.039,0 -T 33,0.053,0 -T 34,0.001,0 -T 42,0.038,0 -T 43,0.087,0 -T 45,0.034,0 -T 46,0.007,0 -T 47,0.066,0 -T 48,0.027,0 -T 50,0.066,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (50)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 1, 10, 11, 13, 17, 18, 19, 19, 28, 32, 32, 33, 34, 42, 43, 45, 46, 47, 48, 50 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 1, 10, 11, 13, 17, 18, 19, 19, 28, 32, 32, 33, 34, 42, 43, 45, 46, 47, 48, 50 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*0.092*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.038*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.004*CONFIGURE_MICROSECONDS_PER_TICK,
                                             13*0.034*CONFIGURE_MICROSECONDS_PER_TICK,
                                             17*0.067*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.083*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.052*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.065*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.078*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.069*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.039*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.053*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.001*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.038*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.087*CONFIGURE_MICROSECONDS_PER_TICK,
                                             45*0.034*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.007*CONFIGURE_MICROSECONDS_PER_TICK,
                                             47*0.066*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             50*0.066*CONFIGURE_MICROSECONDS_PER_TICK
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
