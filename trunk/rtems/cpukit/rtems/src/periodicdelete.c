/*
 *  Periodic Manager -- Delete a Period
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
 *  rtems_periodic_delete
 *
 *  This directive allows a thread to delete a periodic timer.
 *
 *  Input parameters:
 *    id - periodic id
 *
 *  Output parameters:
 *    RTEMS_SUCCESSFUL - if successful
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_periodic_delete(
  rtems_id id
)
{
  Periodic_Control *the_period;
  Objects_Locations       location;

  the_period = _Periodic_Get( id, &location );
  switch ( location ) {

    case OBJECTS_LOCAL:
      _Objects_Close( &_Periodic_Information, &the_period->Object );
      (void) _Watchdog_Remove( &the_period->Timer );
      the_period->state = PERIODIC_INACTIVE;
      _Periodic_Free( the_period );
      _Thread_Enable_dispatch();
      return RTEMS_SUCCESSFUL;

#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:            /* should never return this */
#endif
    case OBJECTS_ERROR:
      break;
  }

  return RTEMS_INVALID_ID;
}

