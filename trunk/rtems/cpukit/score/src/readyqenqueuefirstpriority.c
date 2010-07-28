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
#include <rtems/score/priority.h>
#include <rtems/score/prioritybitmap.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>

/*
 *
 *  _Ready_queue_Enqueue_first_priority
 *
 *  This routine puts @a the_thread to the head of the ready queue. 
 *  For priority-based ready queues, the thread will be the first thread
 *  at its priority level.
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Enqueue_first_priority(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  _Priority_bit_map_Add( &the_thread->sched.priority->Priority_map );
  _Chain_Prepend_unprotected( the_thread->sched.priority->ready_chain, 
      &the_thread->Object.Node );
}
