/*
 *  Rate Monotonic Manager -- Create a Period
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemoncreate.c,v 1.10 2009/12/15 18:26:41 humph Exp $
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
 *  rtems_rate_monotonic_create
 *
 *  This directive creates a rate monotonic timer and performs
 *  some initialization.
 *
 *  Input parameters:
 *    name - name of period
 *    id   - pointer to rate monotonic id
 *
 *  Output parameters:
 *    id               - rate monotonic id
 *    RTEMS_SUCCESSFUL - if successful
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_rate_monotonic_create(
  rtems_name  name,
  rtems_id   *id
)
{
  return (rtems_periodic_create( name, id ));
}