/*
 *  Rate Monotonic Manager -- Cancel a Period
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemoncancel.c,v 1.10 2009/12/15 18:26:41 humph Exp $
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
#include <rtems/rtems/ratemon.h>
#include <rtems/score/thread.h>

/*PAGE
 *
 *  rtems_rate_monotonic_cancel
 *
 *  This directive allows a thread to cancel a rate monotonic timer.
 *
 *  Input parameters:
 *    id - rate monotonic id
 *
 *  Output parameters:
 *    RTEMS_SUCCESSFUL - if successful and caller is not the owning thread
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_rate_monotonic_cancel(
  rtems_id id
)
{
  return (rtems_periodic_cancel(id));
}
