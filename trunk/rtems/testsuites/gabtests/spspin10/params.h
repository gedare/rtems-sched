/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 1,0.032,0 -T 4,0.083,0 -T 9,0.077,0 -T 21,0.065,0 -T 24,0.038,0 -T 25,0.015,0 -T 27,0.049,0 -T 31,0.087,0 -T 33,0.008,0 -T 34,0.046,0 -T 34,0.016,0 -T 34,0.085,0 -T 35,0.012,0 -T 35,0.074,0 -T 36,0.080,0 -T 37,0.087,0 -T 42,0.045,0 -T 43,0.063,0 -T 48,0.014,0 -T 49,0.025,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (49)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 1, 4, 9, 21, 24, 25, 27, 31, 33, 34, 34, 34, 35, 35, 36, 37, 42, 43, 48, 49 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 1, 4, 9, 21, 24, 25, 27, 31, 33, 34, 34, 34, 35, 35, 36, 37, 42, 43, 48, 49 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*0.032*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*0.083*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.077*CONFIGURE_MICROSECONDS_PER_TICK,
                                             21*0.065*CONFIGURE_MICROSECONDS_PER_TICK,
                                             24*0.038*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.015*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.049*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.087*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.008*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.046*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.016*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.085*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.012*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.074*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.08*CONFIGURE_MICROSECONDS_PER_TICK,
                                             37*0.087*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.045*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.063*CONFIGURE_MICROSECONDS_PER_TICK,
                                             48*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.025*CONFIGURE_MICROSECONDS_PER_TICK
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
