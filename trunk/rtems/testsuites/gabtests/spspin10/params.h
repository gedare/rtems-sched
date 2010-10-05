/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 2,0.065,0 -T 4,0.033,0 -T 9,0.017,0 -T 10,0.029,0 -T 11,0.017,0 -T 12,0.024,0 -T 13,0.013,0 -T 17,0.020,0 -T 18,0.011,0 -T 18,0.014,0 -T 19,0.032,0 -T 19,0.020,0 -T 19,0.025,0 -T 22,0.002,0 -T 22,0.002,0 -T 23,0.006,0 -T 25,0.019,0 -T 26,0.031,0 -T 27,0.028,0 -T 28,0.058,0 -T 30,0.031,0 -T 30,0.008,0 -T 31,0.005,0 -T 32,0.015,0 -T 34,0.006,0 -T 34,0.006,0 -T 34,0.014,0 -T 36,0.021,0 -T 37,0.028,0 -T 38,0.035,0 -T 39,0.006,0 -T 41,0.027,0 -T 42,0.002,0 -T 43,0.007,0 -T 46,0.015,0 -T 46,0.017,0 -T 48,0.014,0 -T 48,0.026,0 -T 48,0.029,0 -T 49,0.024,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (49)
#define  NUM_PERIODIC_TASKS         (40)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 2, 4, 9, 10, 11, 12, 13, 17, 18, 18, 19, 19, 19, 22, 22, 23, 25, 26, 27, 28, 30, 30, 31, 32, 34, 34, 34, 36, 37, 38, 39, 41, 42, 43, 46, 46, 48, 48, 48, 49 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 2, 4, 9, 10, 11, 12, 13, 17, 18, 18, 19, 19, 19, 22, 22, 23, 25, 26, 27, 28, 30, 30, 31, 32, 34, 34, 34, 36, 37, 38, 39, 41, 42, 43, 46, 46, 48, 48, 48, 49 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             2*0.065*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*0.033*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.029*CONFIGURE_MICROSECONDS_PER_TICK,
                                             11*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.024*CONFIGURE_MICROSECONDS_PER_TICK,
                                             13*0.013*CONFIGURE_MICROSECONDS_PER_TICK,
                                             17*0.02*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.011*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.032*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.02*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.025*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             23*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.019*CONFIGURE_MICROSECONDS_PER_TICK,
                                             26*0.031*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.028*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.058*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.031*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.008*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.005*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.021*CONFIGURE_MICROSECONDS_PER_TICK,
                                             37*0.028*CONFIGURE_MICROSECONDS_PER_TICK,
                                             38*0.035*CONFIGURE_MICROSECONDS_PER_TICK,
                                             39*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             41*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.007*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.026*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.029*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.024*CONFIGURE_MICROSECONDS_PER_TICK
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
