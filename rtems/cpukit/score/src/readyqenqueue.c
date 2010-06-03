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
 *  _Ready_queue_Enqueue
 *
 *  This routine puts @a the_thread on to the ready queue.
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Enqueue(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{

#if 0
#if defined(RTEMS_MULTIPROCESSING)
  if ( _Thread_MP_Is_receive( the_thread ) && the_thread->receive_packet )
    the_thread = _Thread_MP_Allocate_proxy( the_ready_queue->state );
  else
#endif

  /*
   *  Set the blocking state for this thread queue in the thread.
   */
  _Thread_Set_state( the_thread, the_ready_queue->state );
#endif

#if 0
  /* TODO: this might be a good place to instrument periodic tasks? */
  /*
   *  If the thread wants to timeout, then schedule its timer.
   */
  if ( timeout ) {
    _Watchdog_Initialize(
       &the_thread->Timer,
       handler,
       the_thread->Object.id,
       NULL
    );

    _Watchdog_Insert_ticks( &the_thread->Timer, timeout );
  }
#endif

  /*
   *  Now enqueue the thread per the discipline for this thread queue.
   */
  if ( the_ready_queue->discipline == READY_QUEUE_DISCIPLINE_PRIORITY )
    _Ready_queue_Enqueue_priority(the_ready_queue, the_thread);
  else /* must be READY_QUEUE_DISCIPLINE_FIFO */
    _Ready_queue_Enqueue_fifo(the_ready_queue, the_thread);
}
