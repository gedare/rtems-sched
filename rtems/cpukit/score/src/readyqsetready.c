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
//#include <rtems/score/rqdata.h>

/*PAGE
 *
 *  _Ready_queue_Set_ready
 *
 *  This routine sets @a the_thread->ready based on the queuing discipline.
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *    the_thread      - pointer to thread being manipulated
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_Set_ready(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{

  /*
   *  Set thread->ready per the discipline for this readyq.
   */
  if ( the_ready_queue->discipline == READY_QUEUE_DISCIPLINE_PRIORITY )
    _Ready_queue_Set_ready_priority(the_ready_queue, the_thread);
  else /* must be READY_QUEUE_DISCIPLINE_FIFO */
    _Ready_queue_Set_ready_fifo(the_ready_queue, the_thread);

}
