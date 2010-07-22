/*
 *  Periodic Manager -- Create a Period
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
 *  rtems_periodic_create
 *
 *  This directive creates a periodic timer and performs
 *  some initialization.
 *
 *  Input parameters:
 *    name - name of period
 *    id   - pointer to periodic id
 *
 *  Output parameters:
 *    id               - periodic id
 *    RTEMS_SUCCESSFUL - if successful
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_periodic_create(
  rtems_name  name,
  rtems_id   *id
)
{
  Periodic_Control *the_period;

  if ( !rtems_is_name_valid( name ) )
    return RTEMS_INVALID_NAME;

  if ( !id )
    return RTEMS_INVALID_ADDRESS;

  _Thread_Disable_dispatch();            /* to prevent deletion */

  the_period = _Periodic_Allocate();

  if ( !the_period ) {
    _Thread_Enable_dispatch();
    return RTEMS_TOO_MANY;
  }

  the_period->owner = _Thread_Executing;
  the_period->state = PERIODIC_INACTIVE;

  /* TODO: set periodic flag */

  _Watchdog_Initialize( &the_period->Timer, NULL, 0, NULL );

  _Periodic_Reset_statistics( the_period );

  _Objects_Open(
    &_Periodic_Information,
    &the_period->Object,
    (Objects_Name) name
  );

  *id = the_period->Object.id;
  _Thread_Enable_dispatch();
  return RTEMS_SUCCESSFUL;
}

