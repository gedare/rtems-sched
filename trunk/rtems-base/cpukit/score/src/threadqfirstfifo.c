/*
 *  Thread Queue Handler
 *
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: threadqfirstfifo.c,v 1.7 2010/11/25 09:27:06 sh Exp $
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
#include <rtems/score/threadq.h>
#include <rtems/score/tqdata.h>

/*PAGE
 *
 *  _Thread_queue_First_fifo
 *
 *  This routines returns a pointer to the first thread on the
 *  specified threadq.
 *
 *  Input parameters:
 *    the_thread_queue - pointer to threadq
 *
 *  Output parameters:
 *    returns - first thread or NULL
 */

Thread_Control *_Thread_queue_First_fifo(
  Thread_queue_Control *the_thread_queue
)
{
  if ( !_Chain_Is_empty( &the_thread_queue->Queues.Fifo ) )
    return (Thread_Control *) _Chain_First( &the_thread_queue->Queues.Fifo );

  return NULL;
}
