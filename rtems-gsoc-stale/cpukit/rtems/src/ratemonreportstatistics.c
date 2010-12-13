/*
 *  Rate Monotonic Manager -- Report Statistics for All Periods
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemonreportstatistics.c,v 1.12 2009/12/02 18:22:18 humph Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include <rtems/rtems/periodic.h>

#include <rtems/bspIo.h>
#include <rtems/score/timespec.h>

/*
 *  This directive allows a thread to print the statistics information
 *  on ALL period instances which have non-zero counts using printk.
 *
 *  The implementation of this directive straddles the fence between
 *  inside and outside of RTEMS.  It is presented as part of the Manager
 *  but actually uses other services of the Manager.
 */
void rtems_rate_monotonic_report_statistics_with_plugin(
  void                  *context,
  rtems_printk_plugin_t  print
)
{
  rtems_periodic_report_statistics_with_plugin( context, print );
}

void rtems_rate_monotonic_report_statistics( void )
{
  rtems_periodic_report_statistics_with_plugin( NULL, printk_plugin );
}
