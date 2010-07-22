/*
 *  Periodic Manager -- Period Statistics
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/periodic.h>
#include <rtems/score/thread.h>

/*PAGE
 *
 *  _Periodic_Initate_statistics
 *
 *  This directive resets the statistics for a given period. 
 *
 *  Input parameters:
 *    the_period              - periodic control
 *
 *  Output parameters:
 *
 */
void _Periodic_Initiate_statistics(
  Periodic_Control *the_period
)
{
  Thread_Control *owning_thread = the_period->owner;

  /*
   *  If using nanosecond statistics, we need to obtain the uptime.
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    Timestamp_Control  uptime;

    _TOD_Get_uptime( &uptime );
  #endif

  /*
   *  Set the starting point and the CPU time used for the statistics.
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    the_period->time_period_initiated = uptime;
  #else
    the_period->time_period_initiated = _Watchdog_Ticks_since_boot;
  #endif

  the_period->cpu_usage_period_initiated = owning_thread->cpu_time_used;

  /*
   *  If using nanosecond statistics and the period's thread is currently
   *  executing, then we need to take into account how much time the
   *  executing thread has run since the last context switch.  When this
   *  routine is invoked from rtems_periodic_period, the owner will
   *  be the executing thread.  When this routine is invoked from
   *  _Periodic_Timeout, it will not.
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    if (owning_thread == _Thread_Executing) {

      Thread_CPU_usage_t ran;

      /*
       *  Adjust the CPU time used to account for the time since last
       *  context switch.
       */
      _Timespec_Subtract(
	&_Thread_Time_of_last_context_switch, &uptime, &ran
      );

      _Timespec_Add_to( &the_period->cpu_usage_period_initiated, &ran );
    }
  #endif
    
    /* TODO: scheduler-specific job release */
}

/*PAGE
 *
 *  _Periodic_Update_statistics
 *
 *  This directive updates the statistics for a given period. 
 *
 *  Input parameters:
 *    the_period              - periodic control
 *
 *  Output parameters:
 *
 */
void _Periodic_Update_statistics(
  Periodic_Control    *the_period
)
{
  Thread_CPU_usage_t              executed;
  Periodic_Period_time_t    since_last_period;
  Periodic_Statistics      *stats;
  bool                            valid_status;

  /*
   *  Assume we are only called in states where it is appropriate
   *  to update the statistics.  This should only be PERIODIC_ACTIVE
   *  and PERIODIC_EXPIRED.
   */

  /*
   *  Update the counts.
   */
  stats = &the_period->Statistics;
  stats->count++;

  if ( the_period->state == PERIODIC_EXPIRED )
    stats->missed_count++;

  /*
   *  Grab status for time statistics.
   */
  valid_status =
    _Periodic_Get_status( the_period, &since_last_period, &executed );
  if (!valid_status)
    return;

  /*
   *  Update CPU time
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    _Timestamp_Add_to( &stats->total_cpu_time, &executed );

    if ( _Timestamp_Less_than( &executed, &stats->min_cpu_time ) )
      stats->min_cpu_time = executed;

    if ( _Timestamp_Greater_than( &executed, &stats->max_cpu_time ) )
      stats->max_cpu_time = executed;
  #else
    stats->total_cpu_time  += executed;

    if ( executed < stats->min_cpu_time )
      stats->min_cpu_time = executed;

    if ( executed > stats->max_cpu_time )
      stats->max_cpu_time = executed;
  #endif

  /*
   *  Update Wall time
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    _Timestamp_Add_to( &stats->total_wall_time, &since_last_period );

    if ( _Timestamp_Less_than( &since_last_period, &stats->min_wall_time ) )
      stats->min_wall_time = since_last_period;

    if ( _Timestamp_Greater_than( &since_last_period, &stats->max_wall_time ) )
      stats->max_wall_time = since_last_period;
  #else

    /* Sanity check wall time */
    if ( since_last_period < executed )
      since_last_period = executed;

    stats->total_wall_time += since_last_period;

    if ( since_last_period < stats->min_wall_time )
      stats->min_wall_time = since_last_period;

    if ( since_last_period > stats->max_wall_time )
      stats->max_wall_time = since_last_period;
  #endif
}

