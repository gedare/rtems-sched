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
 *  _Ready_queue_fifo_Extract
 *
 *  This routine removes a specific thread from the specified 
 *  fifo-based ready queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to a readyq header
 *    the_thread       - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

void _Ready_queue_fifo_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  _Chain_Extract_unprotected( &the_thread->Object.Node );
}
