/*
 *  Rate Monotonic Manager
 *
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemon.c,v 1.24 2009/01/06 05:02:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/rtems/periodic.h>
#include <rtems/rtems/ratemon.h>
#include <rtems/score/thread.h>

/*PAGE
 *
 *  _Rate_monotonic_Manager_initialization
 *
 *  This routine initializes all Rate Monotonic Manager related
 *  data structures.
 *
 *  Input parameters:   NONE
 *
 *  Output parameters:  NONE
 *
 *  NOTE: The Rate Monotonic Manager is built on top of the Watchdog
 *        Handler.
 */

void _Rate_monotonic_Manager_initialization(void)
{
  _Periodic_Manager_initialization();
}
