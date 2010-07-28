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

/*PAGE
 *
 *  _Scheduler_Handler_initialization
 *
 *  This routine initializes the scheduler
 *
 *  Input parameters:
 *
 *  Output parameters: NONE
 */

void _Scheduler_Handler_initialization( )
{
  Scheduler_Control *the_scheduler = &_Scheduler;

  /* call the sched_init function registered in the Configuration Scheduler 
   * Table. */
  (*(_Scheduler_Table[Configuration.scheduler_policy].sched_init))(
      the_scheduler
  );
}
