/*
 *  Periodic Manager
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

#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>

#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/periodic.h>
#include <rtems/score/thread.h>

/* TODO: 
 * This is currently wrapped by _Rate_monotonic_Manager_initialization. 
 * It should be a stand-alone manager in the supercore, that follows the 
 * OBJECTS_INTERNAL_API.  This is a relic of being copied directly from 
 * the Rate Monotonic Manager code base.
 */

/*PAGE
 *
 *  _Periodic_Manager_initialization
 *
 *  This routine initializes all Periodic Manager related
 *  data structures.
 *
 *  Input parameters:   NONE
 *
 *  Output parameters:  NONE
 *
 *  NOTE: The Periodic Manager is built on top of the Watchdog
 *        Handler.
 */

void _Periodic_Manager_initialization(void)
{
  _Objects_Initialize_information(
    &_Periodic_Information,    /* object information table */
    OBJECTS_CLASSIC_API,             /* object API */
    OBJECTS_RTEMS_PERIODS,           /* object class */
    Configuration_RTEMS_API.maximum_periods,
                                     /* maximum objects of this class */
    sizeof( Periodic_Control ),/* size of this object's control block */
    false,                           /* true if the name is a string */
    RTEMS_MAXIMUM_NAME_LENGTH        /* maximum length of an object name */
#if defined(RTEMS_MULTIPROCESSING)
    ,
    false,                           /* true if this is a global object class */
    NULL                             /* Proxy extraction support callout */
#endif
  );
}


