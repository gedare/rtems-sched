/*
 *  Periodic Manager -- Cancel a Period
 *
 *  COPYRIGHT (c) 1989-2007.
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
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/rtems/periodic.h>
#include <rtems/score/thread.h>

/*PAGE
 *
 *  rtems_periodic_cancel
 *
 *  This directive allows a thread to cancel a periodic timer.
 *
 *  Input parameters:
 *    id - periodic id
 *
 *  Output parameters:
 *    RTEMS_SUCCESSFUL - if successful and caller is not the owning thread
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_periodic_cancel(
  rtems_id id
)
{
  Periodic_Control *the_period;
  Objects_Locations       location;

  the_period = _Periodic_Get( id, &location );
  switch ( location ) {

    case OBJECTS_LOCAL:
      if ( !_Thread_Is_executing( the_period->owner ) ) {
        _Thread_Enable_dispatch();
        return RTEMS_NOT_OWNER_OF_RESOURCE;
      }
      (void) _Watchdog_Remove( &the_period->Timer );
      the_period->state = PERIODIC_INACTIVE;
      _Thread_Enable_dispatch();
      return RTEMS_SUCCESSFUL;

#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:
#endif
    case OBJECTS_ERROR:
      break;
  }

  return RTEMS_INVALID_ID;
}
