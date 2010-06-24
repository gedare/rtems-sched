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
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>
#include <rtems/score/rqdata.h>

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
  
  switch (Configuration.scheduler_policy) {
    case _SCHED_PRI:
      _Ready_queue_Initialize(
        &_Thread_Ready_queue, 
        READY_QUEUE_DISCIPLINE_PRIORITY
      );
      break;

    case _SCHED_FIFO:
      _Ready_queue_Initialize(
        &_Thread_Ready_queue, 
        READY_QUEUE_DISCIPLINE_FIFO
      );
      break;     

    default:
      while (1);  /* should be _Internal_error_Occurred */
  }

}
