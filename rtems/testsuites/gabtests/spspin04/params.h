/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 1,0.051,0 -T 3,0.053,0 -T 3,0.009,0 -T 15,0.074,0 -T 16,0.063,0 -T 17,0.006,0 -T 19,0.061,0 -T 22,0.027,0 -T 25,0.025,0 -T 28,0.073,0 -T 33,0.047,0 -T 36,0.012,0 -T 38,0.021,0 -T 38,0.110,0 -T 40,0.097,0 -T 42,0.041,0 -T 43,0.048,0 -T 44,0.079,0 -T 49,0.057,0 -T 49,0.047,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (49)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 1, 3, 3, 15, 16, 17, 19, 22, 25, 28, 33, 36, 38, 38, 40, 42, 43, 44, 49, 49 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 1, 3, 3, 15, 16, 17, 19, 22, 25, 28, 33, 36, 38, 38, 40, 42, 43, 44, 49, 49 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             1*0.051*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.053*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.009*CONFIGURE_MICROSECONDS_PER_TICK,
                                             15*0.074*CONFIGURE_MICROSECONDS_PER_TICK,
                                             16*0.063*CONFIGURE_MICROSECONDS_PER_TICK,
                                             17*0.006*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.061*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.025*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.073*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.047*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.012*CONFIGURE_MICROSECONDS_PER_TICK,
                                             38*0.021*CONFIGURE_MICROSECONDS_PER_TICK,
                                             38*0.11*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.097*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.041*CONFIGURE_MICROSECONDS_PER_TICK,
                                             43*0.048*CONFIGURE_MICROSECONDS_PER_TICK,
                                             44*0.079*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.057*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.047*CONFIGURE_MICROSECONDS_PER_TICK
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
