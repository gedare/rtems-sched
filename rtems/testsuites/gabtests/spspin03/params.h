/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 3,0.031,0 -T 3,0.056,0 -T 3,0.056,0 -T 4,0.037,0 -T 10,0.074,0 -T 12,0.001,0 -T 16,0.097,0 -T 24,0.091,0 -T 25,0.024,0 -T 25,0.042,0 -T 26,0.075,0 -T 27,0.096,0 -T 31,0.044,0 -T 32,0.056,0 -T 33,0.045,0 -T 35,0.052,0 -T 36,0.020,0 -T 37,0.001,0 -T 37,0.020,0 -T 40,0.083,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (40)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 3, 3, 3, 4, 10, 12, 16, 24, 25, 25, 26, 27, 31, 32, 33, 35, 36, 37, 37, 40 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 3, 3, 3, 4, 10, 12, 16, 24, 25, 25, 26, 27, 31, 32, 33, 35, 36, 37, 37, 40 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.031*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.056*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.056*CONFIGURE_MICROSECONDS_PER_TICK,
                                             4*0.037*CONFIGURE_MICROSECONDS_PER_TICK,
                                             10*0.074*CONFIGURE_MICROSECONDS_PER_TICK,
                                             12*0.001*CONFIGURE_MICROSECONDS_PER_TICK,
                                             16*0.097*CONFIGURE_MICROSECONDS_PER_TICK,
                                             24*0.091*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.024*CONFIGURE_MICROSECONDS_PER_TICK,
                                             25*0.042*CONFIGURE_MICROSECONDS_PER_TICK,
                                             26*0.075*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.096*CONFIGURE_MICROSECONDS_PER_TICK,
                                             31*0.044*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.056*CONFIGURE_MICROSECONDS_PER_TICK,
                                             33*0.045*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.052*CONFIGURE_MICROSECONDS_PER_TICK,
                                             36*0.02*CONFIGURE_MICROSECONDS_PER_TICK,
                                             37*0.001*CONFIGURE_MICROSECONDS_PER_TICK,
                                             37*0.02*CONFIGURE_MICROSECONDS_PER_TICK,
                                             40*0.083*CONFIGURE_MICROSECONDS_PER_TICK
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
