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
 * 
 * This is currently unused.
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
 *  _Ready_queue_Flush
 *
 *  This kernel routine flushes the given ready queue.
 *
 *  Input parameters:
 *    the_ready_queue       - pointer to readyq to be flushed
 *    remote_extract_callout - pointer to routine which extracts a remote thread
 *    status                 - status to return to the thread
 *
 *  Output parameters:  NONE
 */

void _Ready_queue_Flush(
  Ready_queue_Control       *the_ready_queue,
#if defined(RTEMS_MULTIPROCESSING)
  Ready_queue_Flush_callout  remote_extract_callout,
#else
  Ready_queue_Flush_callout  remote_extract_callout __attribute__((unused)),
#endif
  uint32_t                    status
)
{
  Thread_Control *the_thread;

  while ( (the_thread = _Ready_queue_Dequeue( the_ready_queue )) ) {
#if defined(RTEMS_MULTIPROCESSING)
    if ( !_Objects_Is_local_id( the_thread->Object.id ) )
      ( *remote_extract_callout )( the_thread );
    else
#endif
      the_thread->Wait.return_code = status;
  }
}
