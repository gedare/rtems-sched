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
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/readyq.h>

/*
 *
 *  _Ready_queue_Set_ready_priority
 *
 *  This routine sets @a the_thread->ready for priority-based ready queue
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *    the_thread      - pointer to thread being manipulated
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Set_ready_priority(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  the_thread->ready.priority.ready_chain = &the_ready_queue->Queues.Priority[ 
    _Priority_Get_value(the_thread->current_priority) 
  ];

  _Priority_Initialize_information( &the_thread->ready.priority.Priority_map, 
      the_thread->current_priority );
}
