/*
 *  Thread Handler
 *
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: thread.c,v 1.63 2010/06/29 00:34:12 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/score/apiext.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/states.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>
#include <rtems/config.h>

/*PAGE
 *
 *  _Thread_Handler_initialization
 *
 *  This routine initializes all thread manager related data structures.
 *
 *  Input parameters:   NONE
 *
 *  Output parameters:  NONE
 */

void _Thread_Handler_initialization(void)
{
  uint32_t     ticks_per_timeslice;
  uint32_t     maximum_extensions;
  #if defined(RTEMS_MULTIPROCESSING)
    uint32_t   maximum_proxies;
  #endif

  ticks_per_timeslice = Configuration.ticks_per_timeslice;
  maximum_extensions  = Configuration.maximum_extensions;
  #if defined(RTEMS_MULTIPROCESSING)
    maximum_proxies   =  _Configuration_MP_table->maximum_proxies;
  #endif
  /*
   * BOTH stacks hooks must be set or both must be NULL.
   * Do not allow mixture.
   */
    if ( !( (!Configuration.stack_allocate_hook)
            == (!Configuration.stack_free_hook) ) )
    _Internal_error_Occurred(
      INTERNAL_ERROR_CORE,
      true,
      INTERNAL_ERROR_BAD_STACK_HOOK
    );

  _Thread_Dispatch_necessary = false;
  _Thread_Executing         = NULL;
  _Thread_Heir              = NULL;
#if ( CPU_HARDWARE_FP == TRUE ) || ( CPU_SOFTWARE_FP == TRUE )
  _Thread_Allocated_fp      = NULL;
#endif

  _Thread_Maximum_extensions = maximum_extensions;

  _Thread_Ticks_per_timeslice  = ticks_per_timeslice;

  _Scheduler_Initialize( );

#if defined(RTEMS_MULTIPROCESSING)
  _Thread_MP_Handler_initialization( maximum_proxies );
#endif

  /*
   *  Initialize this class of objects.
   */

  _Objects_Initialize_information(
    &_Thread_Internal_information,
    OBJECTS_INTERNAL_API,
    OBJECTS_INTERNAL_THREADS,
#if defined(RTEMS_MULTIPROCESSING)
    ( _System_state_Is_multiprocessing ) ?  2 : 1,
#else
    1,
#endif
    sizeof( Thread_Control ),
                                /* size of this object's control block */
    false,                      /* true if names for this object are strings */
    8                           /* maximum length of each object's name */
#if defined(RTEMS_MULTIPROCESSING)
    ,
    false,                      /* true if this is a global object class */
    NULL                        /* Proxy extraction support callout */
#endif
  );

}
