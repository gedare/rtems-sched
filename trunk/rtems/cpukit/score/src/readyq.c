/*
 *  Ready Queue Handler
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
#include <rtems/score/chain.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqfifo.h>
#include <rtems/score/readyqpriority.h>
#include <rtems/score/wkspace.h>
#include <rtems/config.h>

/*PAGE
 *
 *  _Ready_queue_Initialize
 *
 *  This routine initializes the specified readyq.
 *
 *  Input parameters:
 *    the_ready_queue      - pointer to a readyq header
 *
 *  Output parameters: NONE
 */

void _Ready_queue_Initialize(
  Ready_queue_Control         *the_ready_queue
)
{
  switch (Configuration.scheduler_policy) {
    case _SCHED_PRI:
      _Ready_queue_Initialize_priority( the_ready_queue );
    break;

    case _SCHED_FIFO:
      _Ready_queue_Initialize_fifo( the_ready_queue );
    break;

    default:
      while(1); /* should be easy to find */
    break;
  }
}
