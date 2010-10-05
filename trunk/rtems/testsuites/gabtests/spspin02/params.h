/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 3,0.013,0 -T 3,0.003,0 -T 3,0.002,0 -T 3,0.013,0 -T 3,0.007,0 -T 5,0.028,0 -T 5,0.016,0 -T 7,0.010,0 -T 7,0.013,0 -T 10,0.045,0 -T 10,0.023,0 -T 11,0.014,0 -T 12,0.008,0 -T 15,0.010,0 -T 18,0.016,0 -T 19,0.042,0 -T 20,0.032,0 -T 21,0.023,0 -T 23,0.005,0 -T 25,0.029,0 -T 25,0.014,0 -T 25,0.031,0 -T 26,0.030,0 -T 27,0.002,0 -T 29,0.006,0 -T 29,0.012,0 -T 30,0.060,0 -T 31,0.051,0 -T 33,0.006,0 -T 35,0.019,0 -T 36,0.003,0 -T 40,0.002,0 -T 40,0.007,0 -T 41,0.031,0 -T 42,0.025,0 -T 43,0.027,0 -T 43,0.011,0 -T 44,0.041,0 -T 45,0.055,0 -T 48,0.017,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (48)
#define  NUM_PERIODIC_TASKS         (40)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 3, 3, 3, 3, 3, 5, 5, 7, 7, 10, 10, 11, 12, 15, 18, 19, 20, 21, 23, 25, 25, 25, 26, 27, 29, 29, 30, 31, 33, 35, 36, 40, 40, 41, 42, 43, 43, 44, 45, 48 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 3, 3, 3, 3, 3, 5, 5, 7, 7, 10, 10, 11, 12, 15, 18, 19, 20, 21, 23, 25, 25, 25, 26, 27, 29, 29, 30, 31, 33, 35, 36, 40, 40, 41, 42, 43, 43, 44, 45, 48 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.003*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.007*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*0.028*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*0.016*CONFIGURE_MICROSECONDS_PER_TICK,
                                             7*0.01*CONFIGURE_MICROSECONDS_PER_TICK,
                                             7*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.045*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.023*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.008*CONFIGURE_MICROSECONDS_PER_TICK,
                                             15*0.01*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.016*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.042*CONFIGURE_MICROSECONDS_PER_TICK,
                                             20*0.032*CONFIGURE_MICROSECONDS_PER_TICK,
                                             21*0.023*CONFIGURE_MICROSECONDS_PER_TICK,
                                             23*0.005*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.029*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.031*CONFIGURE_MICROSECONDS_PER_TICK,
                                             26*0.03*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.012*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.06*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.051*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.019*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.003*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.007*CONFIGURE_MICROSECONDS_PER_TICK,
                                             41*0.031*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.025*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.011*CONFIGURE_MICROSECONDS_PER_TICK,
                                             44*0.041*CONFIGURE_MICROSECONDS_PER_TICK,
                                             45*0.055*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.017*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

uint32_t  Phases[1+NUM_TASKS]           = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
Task_name[ 21 ] =  rtems_build_name( 'P', 'T', '2', '1' );\
Task_name[ 22 ] =  rtems_build_name( 'P', 'T', '2', '2' );\
Task_name[ 23 ] =  rtems_build_name( 'P', 'T', '2', '3' );\
Task_name[ 24 ] =  rtems_build_name( 'P', 'T', '2', '4' );\
Task_name[ 25 ] =  rtems_build_name( 'P', 'T', '2', '5' );\
Task_name[ 26 ] =  rtems_build_name( 'P', 'T', '2', '6' );\
Task_name[ 27 ] =  rtems_build_name( 'P', 'T', '2', '7' );\
Task_name[ 28 ] =  rtems_build_name( 'P', 'T', '2', '8' );\
Task_name[ 29 ] =  rtems_build_name( 'P', 'T', '2', '9' );\
Task_name[ 30 ] =  rtems_build_name( 'P', 'T', '3', '0' );\
Task_name[ 31 ] =  rtems_build_name( 'P', 'T', '3', '1' );\
Task_name[ 32 ] =  rtems_build_name( 'P', 'T', '3', '2' );\
Task_name[ 33 ] =  rtems_build_name( 'P', 'T', '3', '3' );\
Task_name[ 34 ] =  rtems_build_name( 'P', 'T', '3', '4' );\
Task_name[ 35 ] =  rtems_build_name( 'P', 'T', '3', '5' );\
Task_name[ 36 ] =  rtems_build_name( 'P', 'T', '3', '6' );\
Task_name[ 37 ] =  rtems_build_name( 'P', 'T', '3', '7' );\
Task_name[ 38 ] =  rtems_build_name( 'P', 'T', '3', '8' );\
Task_name[ 39 ] =  rtems_build_name( 'P', 'T', '3', '9' );\
Task_name[ 40 ] =  rtems_build_name( 'P', 'T', '4', '0' );\
} while(0)

#endif
