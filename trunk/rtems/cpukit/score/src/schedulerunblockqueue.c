/*
 *  Scheduler Handler
 *
 *
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/apiext.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/states.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>

/*
 *
 *  _Scheduler_Unblock_queue
 *
 *  This kernel routine readies the requested thread according to the queuing 
 *  discipline. A new heir thread may be selected.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread - pointer to thread control block
 *
 *  Output parameters:  NONE
 *
 *  NOTE:  This routine uses the "blocking" heir selection mechanism.
 *         This ensures the correct heir after a thread restart.
 *
 *  INTERRUPT LATENCY:
 */

void _Scheduler_Unblock_queue(
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
)
{
  Thread_Control *heir;

  _Ready_queue_Enqueue(&the_scheduler->ready_queue, the_thread);

  /* TODO: flash critical section */
  /* XXX */

  _Scheduler_Schedule(the_scheduler);

  heir = _Thread_Heir;

  /*
   * See if the heir is executing. if not, then the newly queue'd thread may
   * cause a new dispatch.
   *
   *  Normal case:
   *    If the current thread is preemptible, then we need to do
   *    a context switch.
   *  Pseudo-ISR case:
   *    Even if the thread isn't preemptible, if the new heir is
   *    a pseudo-ISR system task, we need to do a context switch.
   */
  if ( !_Thread_Is_executing( heir ) ) {
    if ( _Thread_Executing->is_preemptible || 
         _Priority_Get_value(the_thread->current_priority) == 0 )
      _Dispatch_needed = true;
  }

  return;
}
