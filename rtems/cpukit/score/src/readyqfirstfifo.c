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
#include <rtems/score/rqdata.h>

/*PAGE
 *
 *  _Ready_queue_First_fifo
 *
 *  This routines returns a pointer to the first thread on the
 *  specified readyq.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *
 *  Output parameters:
 *    returns - first thread or NULL
 */

Thread_Control *_Ready_queue_First_fifo(
  Ready_queue_Control *the_ready_queue
)
{
  if ( !_Chain_Is_empty( &the_ready_queue->Queues.Fifo ) )
    return (Thread_Control *) the_ready_queue->Queues.Fifo.first;

  return NULL;
}