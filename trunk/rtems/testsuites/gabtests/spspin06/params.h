/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 7,0.068,0 -T 9,0.084,0 -T 9,0.062,0 -T 10,0.040,0 -T 11,0.032,0 -T 11,0.040,0 -T 12,0.030,0 -T 16,0.054,0 -T 18,0.068,0 -T 21,0.053,0 -T 22,0.001,0 -T 27,0.062,0 -T 28,0.040,0 -T 29,0.083,0 -T 31,0.064,0 -T 35,0.033,0 -T 35,0.054,0 -T 45,0.019,0 -T 46,0.043,0 -T 50,0.070,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (50)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 7, 9, 9, 10, 11, 11, 12, 16, 18, 21, 22, 27, 28, 29, 31, 35, 35, 45, 46, 50 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 7, 9, 9, 10, 11, 11, 12, 16, 18, 21, 22, 27, 28, 29, 31, 35, 35, 45, 46, 50 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             7*0.068*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.084*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.062*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.04*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.032*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.04*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.03*CONFIGURE_MICROSECONDS_PER_TICK,
                                             16*0.054*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.068*CONFIGURE_MICROSECONDS_PER_TICK,
                                             21*0.053*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.001*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.062*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.04*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.083*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.064*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.033*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.054*CONFIGURE_MICROSECONDS_PER_TICK,
                                             45*0.019*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.043*CONFIGURE_MICROSECONDS_PER_TICK,
                                             50*0.07*CONFIGURE_MICROSECONDS_PER_TICK
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
