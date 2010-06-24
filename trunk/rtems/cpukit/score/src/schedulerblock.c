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

/*PAGE
 *
 * _Scheduler_Block
 *
 * This kernel routine removes the_thread from scheduling decisions.
 *
 * Input parameters:
 *   the_thread   - pointer to thread control block
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Scheduler_Block(
  Thread_Control   *the_thread
)
{

  _Ready_queue_Extract(&_Thread_Ready_queue, the_thread);

  /* TODO: flash critical section */
  /* XXX */

  /* TODO: Is this robust? */
  if ( _Thread_Is_heir( the_thread ) )
     _Scheduler_Schedule();

  /* TODO: rewrite _Context_Switch_necessary to dispatch_needed */
  if ( _Thread_Is_executing( the_thread ) )
    _Context_Switch_necessary = true;

  return;
}
