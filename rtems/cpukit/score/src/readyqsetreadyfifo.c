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
 *  _Ready_queue_Set_ready_fifo
 *
 *  This routine sets @a the_thread->ready for fifo ready queue
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *    the_thread      - pointer to thread being manipulated
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Set_ready_fifo(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  /* TODO: this probably is not needed */
  the_thread->ready.fifo.ready_chain = &the_ready_queue->Queues.Fifo; 
}
