/*
 *  Periodic Manager -- Get Status
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
 *  _Periodic_Get_status
 *
 *  This directive allows a thread to obtain status information on a
 *  period.
 *
 *  Input parameters:
 *    the_period              - periodic control
 *    wall_since_last_period  - wall time between period invocations
 *    cpu_since_last_period   - cpu time between period invocations
 *
 *  Output parameters:
 *    true        - if successful
 *    false       - if unsuccessful
 *
 */
bool _Periodic_Get_status(
  Periodic_Control        *the_period,
  Periodic_Period_time_t  *wall_since_last_period,
  Thread_CPU_usage_t            *cpu_since_last_period
)
{
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    Timestamp_Control        uptime;
  #endif
    Thread_Control          *owning_thread = the_period->owner;
    Thread_CPU_usage_t       used;

  /*
   *  Determine elapsed wall time since period initiated.
   */
  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    _TOD_Get_uptime( &uptime );
    _Timestamp_Subtract(
      &the_period->time_period_initiated, &uptime, wall_since_last_period
    );
  #else
    *wall_since_last_period =
      _Watchdog_Ticks_since_boot - the_period->time_period_initiated;
  #endif

  /*
   *  Determine cpu usage since period initiated.
   */
  used = owning_thread->cpu_time_used;

  #ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
    if (owning_thread == _Thread_Executing) {

      Thread_CPU_usage_t ran;

      /* How much time time since last context switch */
      _Timestamp_Subtract(
        &_Thread_Time_of_last_context_switch, &uptime, &ran
      );

      /* cpu usage += ran */
      _Timestamp_Add_to( &used, &ran );

      /*
       *  The cpu usage info was reset while executing.  Can't
       *  determine a status.
       */
      if (_Timestamp_Less_than(&used, &the_period->cpu_usage_period_initiated))
        return false;

       /* used = current cpu usage - cpu usage at start of period */
      _Timestamp_Subtract(
         &the_period->cpu_usage_period_initiated,
         &used,
         cpu_since_last_period
      );
    }
  #else
      /*
       *  The cpu usage info was reset while executing.  Can't
       *  determine a status.
       */
      if (used < the_period->cpu_usage_period_initiated)
        return false;

      *cpu_since_last_period = used - the_period->cpu_usage_period_initiated;
  #endif
  return true;
}

