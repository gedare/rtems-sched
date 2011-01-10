/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 1,0.099,0 -T 2,0.047,0 -T 3,0.068,0 -T 6,0.035,0 -T 9,0.073,0 -T 10,0.010,0 -T 10,0.107,0 -T 14,0.009,0 -T 14,0.033,0 -T 14,0.012,0 -T 17,0.072,0 -T 21,0.087,0 -T 27,0.072,0 -T 28,0.028,0 -T 29,0.022,0 -T 30,0.001,0 -T 32,0.068,0 -T 35,0.033,0 -T 36,0.109,0 -T 40,0.015,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (40)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 1, 2, 3, 6, 9, 10, 10, 14, 14, 14, 17, 21, 27, 28, 29, 30, 32, 35, 36, 40 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 1, 2, 3, 6, 9, 10, 10, 14, 14, 14, 17, 21, 27, 28, 29, 30, 32, 35, 36, 40 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*0.099*CONFIGURE_MICROSECONDS_PER_TICK,
                                             2*0.047*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.068*CONFIGURE_MICROSECONDS_PER_TICK,
                                             6*0.035*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.073*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.01*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.107*CONFIGURE_MICROSECONDS_PER_TICK,
                                             14*0.009*CONFIGURE_MICROSECONDS_PER_TICK,
                                             14*0.033*CONFIGURE_MICROSECONDS_PER_TICK,
                                             14*0.012*CONFIGURE_MICROSECONDS_PER_TICK,
                                             17*0.072*CONFIGURE_MICROSECONDS_PER_TICK,
                                             21*0.087*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.072*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.028*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.022*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.001*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.068*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.033*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.109*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.015*CONFIGURE_MICROSECONDS_PER_TICK
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