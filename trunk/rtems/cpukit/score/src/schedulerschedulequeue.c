/*
 *  Scheduler Handler
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/percpu.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/thread.h>

/*
 *
 * _Scheduler_Schedule_queue
 *
 * This kernel routine implements scheduling decision logic for queue-based
 * scheduling.  Any scheduler that selects the next ready task based on the
 * head of the ready queue can use this function for its schedule routine.
 *
 * Input parameters:
 *   the_scheduler - pointer to scheduler control
 *   the_thread   - pointer to thread control block
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Scheduler_Schedule_queue(
  Scheduler_Control *the_scheduler,
  Thread_Control    *the_thread
)
{
  _Thread_Heir = _Ready_queue_First(&the_scheduler->ready_queue);
}
