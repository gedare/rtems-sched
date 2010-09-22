/*
 *  Periodic Manager - Period Blocking
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
#include <rtems/config.h>
#include <rtems/rtems/periodic.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/periodic.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/scheduleredf.h>
#include <rtems/score/thread.h>


/*PAGE
 *
 *  rtems_periodic_period
 *
 *  This directive allows a thread to manipulate a periodic timer.
 *
 *  Input parameters:
 *    id     - periodic id
 *    length - length of period (in ticks)
 *
 *  Output parameters:
 *    RTEMS_SUCCESSFUL - if successful
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_periodic_period(
  rtems_id       id,
  rtems_interval length
)
{
  Periodic_Control              *the_period;
  Objects_Locations                    location;
  rtems_status_code                    return_value;
  rtems_periodic_period_states   local_state;
  ISR_Level                            level;

  the_period = _Periodic_Get( id, &location );

  switch ( location ) {
    case OBJECTS_LOCAL:
      if ( !_Thread_Is_executing( the_period->owner ) ) {
        _Thread_Enable_dispatch();
        return RTEMS_NOT_OWNER_OF_RESOURCE;
      }

      if ( length == RTEMS_PERIOD_STATUS ) {
        switch ( the_period->state ) {
          case PERIODIC_INACTIVE:
            return_value = RTEMS_NOT_DEFINED;
            break;
          case PERIODIC_EXPIRED:
          case PERIODIC_EXPIRED_WHILE_BLOCKING:
            return_value = RTEMS_TIMEOUT;
            break;
          case PERIODIC_ACTIVE:
          default:              /* unreached -- only to remove warnings */
            return_value = RTEMS_SUCCESSFUL;
            break;
        }
        _Thread_Enable_dispatch();
        return( return_value );
      }

      _ISR_Disable( level );
      if ( the_period->state == PERIODIC_INACTIVE ) {

        _ISR_Enable( level );

        /*
         *  Baseline statistics information for the beginning of a period.
         */
        _Periodic_Initiate_statistics( the_period );

        the_period->state = PERIODIC_ACTIVE;
        _Watchdog_Initialize(
            &the_period->Timer,
            _Periodic_Timeout,
            id,
            NULL
            );

        the_period->next_length = length;

        _Watchdog_Insert_ticks( &the_period->Timer, length );
        _Thread_Enable_dispatch();
        return RTEMS_SUCCESSFUL;
      }

      if ( the_period->state == PERIODIC_ACTIVE ) {
        /*
         *  Update statistics from the concluding period.
         */
        _Periodic_Update_statistics( the_period );

        /* TODO: scheduler-specific job completion call-out */

        /*
         *  This tells the _Periodic_Timeout that this task is
         *  in the process of blocking on the period and that we
         *  may be changing the length of the next period.
         */
        the_period->state = PERIODIC_OWNER_IS_BLOCKING;
        the_period->next_length = length;

        _ISR_Enable( level );

        _Thread_Executing->Wait.id = the_period->Object.id;
        _Thread_Set_state( _Thread_Executing, STATES_WAITING_FOR_PERIOD );

        /*
         *  Did the watchdog timer expire while we were actually blocking
         *  on it?
         */
        _ISR_Disable( level );
        local_state = the_period->state;
        the_period->state = PERIODIC_ACTIVE;
        _ISR_Enable( level );

        /*
         *  If it did, then we want to unblock ourself and continue as
         *  if nothing happen.  The period was reset in the timeout routine.
         */
        if ( local_state == PERIODIC_EXPIRED_WHILE_BLOCKING )
          _Thread_Clear_state( _Thread_Executing, STATES_WAITING_FOR_PERIOD );

        _Thread_Enable_dispatch();
        return RTEMS_SUCCESSFUL;
      }

      if ( the_period->state == PERIODIC_EXPIRED ) {
        /*
         *  Update statistics from the concluding period
         */
        _Periodic_Update_statistics( the_period );

        /* TODO: scheduler-specific job release call-out */
        if (Configuration.scheduler_policy == _Scheduler_EDF)
          _Scheduler_edf_Release_job( the_period );

        _ISR_Enable( level );

        the_period->state = PERIODIC_ACTIVE;
        the_period->next_length = length;

        _Watchdog_Insert_ticks( &the_period->Timer, length );
        _Thread_Enable_dispatch();
        return RTEMS_TIMEOUT;
      }

      /*
       *  These should never happen so just return invalid Id.
       *    - RATE_MONOTONIC_OWNER_IS_BLOCKING:
       *    - RATE_MONOTONIC_EXPIRED_WHILE_BLOCKING:
       */
#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:            /* should never return this */
#endif
    case OBJECTS_ERROR:
      break;
  }

  return RTEMS_INVALID_ID;
}


