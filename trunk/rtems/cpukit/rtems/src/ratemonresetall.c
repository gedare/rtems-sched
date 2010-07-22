/*
 *  Rate Monotonic Manager -- Reset Statistics for All Periods
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemonresetall.c,v 1.2 2007/05/17 22:46:45 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/score/object.h>
#include <rtems/rtems/periodic.h>
#include <rtems/rtems/ratemon.h>
#include <rtems/score/thread.h>

/*
 *  rtems_rate_monotonic_reset_all_statistics
 */
void rtems_rate_monotonic_reset_all_statistics( void )
{
  rtems_periodic_reset_all_statistics();
}
