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
 *  _Ready_queue_Enqueue_priority
 *
 *  This routine puts @a the_thread on to the priority-based ready queue.
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *    the_thread  - pointer to thread
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Enqueue_priority(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  _Priority_Add_bit_map( &the_thread->sched.priority->Priority_map );
  _Chain_Append_unprotected( the_thread->sched.priority->ready_chain, 
      &the_thread->Object.Node );
}
