/*
 *  Scheduler Handler
 *
 *
 *  COPYRIGHT (c) 1989-2008.
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
#include <rtems/score/chain.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerfifo.h>
#include <rtems/score/schedulerpriority.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/**
 * This routine does nothing, and is used as a stub for Sched_allocate_xxx.
 *
 * Note: returns a non-zero value, or else thread initialize thinks the 
 * allocation failed.
 *
 * The overhead of a function call will still be imposed. :(
 */
void * _Scheduler_Sched_allocate_nothing( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
  )
{
  return (void*)-1; /* maybe pick an appropriate poison value */
}


/**
 * This routine does nothing, and is used as a stub for Sched_update_xxx
 *
 * The overhead of a function call will still be imposed. :(
 */
void _Scheduler_Sched_update_nothing( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
  )
{

}

/*PAGE
 *
 *  _Scheduler_Initialize
 *
 *  This routine initializes the scheduler
 *
 *  Input parameters:
 *
 *  Output parameters: NONE
 */

void _Scheduler_Initialize( )
{
  Scheduler_Control *the_scheduler = &_Scheduler;

  switch (Configuration.scheduler_policy) {

    case _SCHED_PRI:
      _Scheduler_Initialize_priority( the_scheduler );
      break;

    case _SCHED_FIFO:
      _Scheduler_Initialize_fifo( the_scheduler );
      break;

    default:
      while ( 1 ); /* should be easy to find */
  }

}