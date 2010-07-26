/*
 *  Scheduler Handler
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
#include <rtems/config.h>
#include <rtems/score/chain.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/prioritybitmap.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/schedulerpriority.h>
#include <rtems/score/schedulerqueue.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Scheduler_Sched_update_priority
 *
 * Updates the sched field of @a the_thread.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread    - pointer to thread control block
 *
 *  Output parameters: NONE
 */

void _Scheduler_Sched_update_priority (
    Scheduler_Control *the_scheduler,
    Thread_Control    *the_thread
)
{
  Ready_queue_Control *rq = &the_scheduler->ready_queue;
  the_thread->sched.priority->ready_chain = &rq->Queues.Priority[ 
      the_thread->current_priority 
    ];

  _Priority_Initialize_information_bit_map( 
      &the_thread->sched.priority->Priority_map, 
      the_thread->current_priority 
  );
}
