/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 5,0.030,0 -T 20,0.101,0 -T 20,0.101,0 -T 22,0.054,0 -T 28,0.121,0 -T 35,0.072,0 -T 37,0.018,0 -T 46,0.002,0 -T 47,0.100,0 -A 200,1,0
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (47)
#define  NUM_PERIODIC_TASKS         (9)
#define  NUM_APERIODIC_TASKS        (1)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 5, 20, 20, 22, 28, 35, 37, 46, 47, 200 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 5, 20, 20, 22, 28, 35, 37, 46, 47 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             5*0.03*CONFIGURE_MICROSECONDS_PER_TICK,
                                             20*0.101*CONFIGURE_MICROSECONDS_PER_TICK,
                                             20*0.101*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.054*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.121*CONFIGURE_MICROSECONDS_PER_TICK,
                                             35*0.072*CONFIGURE_MICROSECONDS_PER_TICK,
                                             37*0.018*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.002*CONFIGURE_MICROSECONDS_PER_TICK,
                                             47*0.1*CONFIGURE_MICROSECONDS_PER_TICK,
                                             200*1*CONFIGURE_MICROSECONDS_PER_TICK
                                             };

uint32_t  Phases[1+NUM_TASKS]           = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
Task_name[ 10 ] =  rtems_build_name( 'A', 'T', '1', '0' );\
} while(0)

#endif
