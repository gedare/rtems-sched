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
 *  _Ready_queue_Initialize
 *
 *  This routine initializes the specified readyq.
 *
 *  Input parameters:
 *    the_ready_queue      - pointer to a readyq header
 *    discipline            - queueing discipline
 *
 *  Output parameters: NONE
 */

void _Ready_queue_Initialize(
  Ready_queue_Control         *the_ready_queue,
  Ready_queue_Disciplines      the_discipline
)
{
  the_ready_queue->discipline     = the_discipline;
      uint32_t   index;

  switch (the_discipline) {
    case READY_QUEUE_DISCIPLINE_PRIORITY:

      for( index=0; index <= PRIORITY_MAXIMUM; index++)
        _Chain_Initialize_empty( &the_ready_queue->Queues.Priority[index] );
    break;

    case READY_QUEUE_DISCIPLINE_FIFO:
      _Chain_Initialize_empty( &the_ready_queue->Queues.Fifo );
    break;

    default:
      while(1); /* should be easy to find */
    break;
  }
}
