/* params.h
 *
 * This is a generated file.
 * Use the gen-headers.lua script to create this file.
 */

/* This file was generated with the following parameters: 
-T 3,0.038,0 -T 8,0.064,0 -T 8,0.011,0 -T 13,0.009,0 -T 20,0.110,0 -T 20,0.050,0 -T 22,0.004,0 -T 22,0.034,0 -T 24,0.037,0 -T 27,0.113,0 -T 28,0.039,0 -T 29,0.104,0 -T 29,0.009,0 -T 30,0.113,0 -T 30,0.069,0 -T 32,0.048,0 -T 34,0.023,0 -T 42,0.035,0 -T 46,0.069,0 -T 49,0.021,0 
*/

#ifndef __PARAMS_H_
#define __PARAMS_H_

#define  HP_LENGTH                  (-1)
#define  MAX_PERIOD                 (49)
#define  NUM_PERIODIC_TASKS         (20)
#define  NUM_APERIODIC_TASKS        (0)
#define  NUM_TASKS                  ( NUM_PERIODIC_TASKS + NUM_APERIODIC_TASKS )
uint32_t  periodic_tasks            = NUM_PERIODIC_TASKS;

rtems_task_priority Priorities[1+NUM_TASKS]= { 0, 3, 8, 8, 13, 20, 20, 22, 22, 24, 27, 28, 29, 29, 30, 30, 32, 34, 42, 46, 49 };

uint32_t  Periods[1+NUM_PERIODIC_TASKS]    = { 0, 3, 8, 8, 13, 20, 20, 22, 22, 24, 27, 28, 29, 29, 30, 30, 32, 34, 42, 46, 49 };

uint32_t  Execution_us[1+NUM_TASKS]        = {
                                             0*CONFIGURE_MICROSECONDS_PER_TICK,
                                             3*0.038*CONFIGURE_MICROSECONDS_PER_TICK,
                                             8*0.064*CONFIGURE_MICROSECONDS_PER_TICK,
                                             8*0.011*CONFIGURE_MICROSECONDS_PER_TICK,
                                             13*0.009*CONFIGURE_MICROSECONDS_PER_TICK,
                                             20*0.11*CONFIGURE_MICROSECONDS_PER_TICK,
                                             20*0.05*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.004*CONFIGURE_MICROSECONDS_PER_TICK,
                                             22*0.034*CONFIGURE_MICROSECONDS_PER_TICK,
                                             24*0.037*CONFIGURE_MICROSECONDS_PER_TICK,
                                             27*0.113*CONFIGURE_MICROSECONDS_PER_TICK,
                                             28*0.039*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.104*CONFIGURE_MICROSECONDS_PER_TICK,
                                             29*0.009*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.113*CONFIGURE_MICROSECONDS_PER_TICK,
                                             30*0.069*CONFIGURE_MICROSECONDS_PER_TICK,
                                             32*0.048*CONFIGURE_MICROSECONDS_PER_TICK,
                                             34*0.023*CONFIGURE_MICROSECONDS_PER_TICK,
                                             42*0.035*CONFIGURE_MICROSECONDS_PER_TICK,
                                             46*0.069*CONFIGURE_MICROSECONDS_PER_TICK,
                                             49*0.021*CONFIGURE_MICROSECONDS_PER_TICK
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
