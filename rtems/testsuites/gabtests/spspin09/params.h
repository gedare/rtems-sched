/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 2,0.002,0 -T 8,0.015,0 -T 10,0.013,0 -T 11,0.013,0 -T 11,0.011,0 -T 12,0.015,0 -T 14,0.017,0 -T 18,0.000,0 -T 22,0.011,0 -T 23,0.007,0 -T 33,0.017,0 -T 35,0.017,0 -T 35,0.005,0 -T 35,0.014,0 -T 36,0.013,0 -T 39,0.003,0 -T 40,0.013,0 -T 41,0.006,0 -T 41,0.002,0 -T 44,0.007,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (44)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 2, 8, 10, 11, 11, 12, 14, 18, 22, 23, 33, 35, 35, 35, 36, 39, 40, 41, 41, 44 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 2, 8, 10, 11, 11, 12, 14, 18, 22, 23, 33, 35, 35, 35, 36, 39, 40, 41, 41, 44 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             2*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             8*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.011*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             14*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.011*CONFIGURE_MICROSECONDS_PER_TICK,
                                             23*0.007*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.005*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             39*0.003*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             41*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             41*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             44*0.007*CONFIGURE_MICROSECONDS_PER_TICK
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
