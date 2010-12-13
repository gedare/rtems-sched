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
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/thread.h>

/*
 *
 * _Scheduler_queue_Block
 *
 * This kernel routine removes the_thread from scheduling decisions based 
 * on simple queue extraction.
 *
 * Input parameters:
 *   the_thread   - pointer to thread control block
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Scheduler_queue_Block(
  Scheduler_Control *the_scheduler,
  Thread_Control   *the_thread
)
{

  _Ready_queue_Extract(&the_scheduler->ready_queue, the_thread);

  /* TODO: flash critical section */
  /* XXX */

  /* TODO: Is this robust? */
  if ( _Thread_Is_heir( the_thread ) )
     _Scheduler_Schedule(the_scheduler);

  if ( _Thread_Is_executing( the_thread ) )
    _Thread_Dispatch_necessary = true;

  return;
}
