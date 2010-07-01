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
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>

/*
 *
 *  _Ready_queue_Requeue_priority
 *
 *  This routine is invoked when a thread changes priority and should be
 *  moved to a different position on the ready queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to a readyq header
 *    the_thread       - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

void _Ready_queue_Requeue_priority(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  if ( !_Chain_Has_only_one_node( the_thread->sched->priority.ready_chain ) ) {
    _Chain_Extract_unprotected( &the_thread->Object.Node );

    _Chain_Append_unprotected( the_thread->sched->priority.ready_chain, 
      &the_thread->Object.Node );
  }
}

