/*
 *  Scheduler Handler -- EDF scheduling
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
#include <rtems/score/scheduleredf.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/watchdog.h>

/*
 *
 *  _Scheduler_edf_Initialize
 *
 * Initializes the scheduler for edf scheduling.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters: NONE
 */

void _Scheduler_edf_Initialize (
    Scheduler_Control *the_scheduler
)
{
  the_scheduler->Operations.schedule           = &_Scheduler_edf_Schedule;
  the_scheduler->Operations.yield              = &_Scheduler_edf_Yield;
  the_scheduler->Operations.block              = &_Scheduler_edf_Block;
  the_scheduler->Operations.unblock            = &_Scheduler_edf_Unblock;
  the_scheduler->Operations.scheduler_allocate = 
      &_Scheduler_edf_Thread_scheduler_allocate;
  the_scheduler->Operations.scheduler_free     = 
      &_Scheduler_edf_Thread_scheduler_free;
  the_scheduler->Operations.scheduler_update   = 
      &_Scheduler_edf_Thread_scheduler_update;

  _Scheduler_edf_Ready_queue_initialize( the_scheduler );
}