/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 4,0.028,0 -T 8,0.043,0 -T 9,0.084,0 -T 10,0.026,0 -T 12,0.053,0 -T 14,0.095,0 -T 16,0.079,0 -T 17,0.014,0 -T 18,0.017,0 -T 19,0.049,0 -T 31,0.037,0 -T 32,0.072,0 -T 34,0.045,0 -T 35,0.078,0 -T 36,0.043,0 -T 36,0.071,0 -T 42,0.027,0 -T 42,0.037,0 -T 44,0.092,0 -T 49,0.010,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (49)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 4, 8, 9, 10, 12, 14, 16, 17, 18, 19, 31, 32, 34, 35, 36, 36, 42, 42, 44, 49 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 4, 8, 9, 10, 12, 14, 16, 17, 18, 19, 31, 32, 34, 35, 36, 36, 42, 42, 44, 49 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*0.028*CONFIGURE_MICROSECONDS_PER_TICK,
                                             8*0.043*CONFIGURE_MICROSECONDS_PER_TICK,
                                             9*0.084*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.026*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.053*CONFIGURE_MICROSECONDS_PER_TICK,
                                             14*0.095*CONFIGURE_MICROSECONDS_PER_TICK,
                                             16*0.079*CONFIGURE_MICROSECONDS_PER_TICK,
                                             17*0.014*CONFIGURE_MICROSECONDS_PER_TICK,
                                             18*0.017*CONFIGURE_MICROSECONDS_PER_TICK,
                                             19*0.049*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.037*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.072*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.045*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.078*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.043*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.071*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.027*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.037*CONFIGURE_MICROSECONDS_PER_TICK,
                                             44*0.092*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.01*CONFIGURE_MICROSECONDS_PER_TICK
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
