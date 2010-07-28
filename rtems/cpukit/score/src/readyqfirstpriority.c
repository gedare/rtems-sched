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
 *  _Ready_queue_First_priority
 *
 *  This routines returns a pointer to the first thread on @a the_ready_queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to thread queue
 *
 *  Output parameters:
 *    returns - first thread or NULL
 */

Thread_Control *_Ready_queue_First_priority(
  Ready_queue_Control *the_ready_queue
)
{
  uint32_t   index = _Priority_bit_map_Get_highest();

  if ( !_Chain_Is_empty( &the_ready_queue->Queues.Priority[ index ] ) )
    return (Thread_Control *) the_ready_queue->Queues.Priority[ index ].first;

  return NULL;
}
