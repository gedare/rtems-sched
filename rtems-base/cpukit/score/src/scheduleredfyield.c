/*
 *  Scheduler Handler
 *
 *  Copyright (C) 2010 Gedare Bloom.
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
#include <rtems/score/scheduler.h>
#include <rtems/score/scheduleredf.h>
#include <rtems/score/states.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>

/*
 *  _Scheduler_edf_Yield
 *
 *  This kernel routine will remove the running THREAD from the ready queue
 *  and place it immediately at the rear of this chain.  Reset timeslice
 *  and yield the processor functions both use this routine, therefore if
 *  reset is true and this is the only thread on the queue then the
 *  timeslice counter is reset.  The heir THREAD will be updated if the
 *  running is also the currently the heir.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *
 *  Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 *    ready chain
 *    select heir
 */

void _Scheduler_edf_Yield( 
    Scheduler_Control   *the_scheduler
)
{
  ISR_Level       level;
  Thread_Control *executing;
  Chain_Control  *ready;

  executing = _Thread_Executing;

  /* tasks with deadline do not yield */
  if (executing->scheduler.edf->deadline.value) {
    return;
  }

  ready = &the_scheduler->Ready_queues.edf->fifo_queue;
  _ISR_Disable( level );
      _Chain_Extract_unprotected( &executing->Object.Node );
      _Chain_Append_unprotected( ready, &executing->Object.Node );
 
      _ISR_Flash( level );

      if ( _Thread_Is_heir( executing ) )
        _Scheduler_edf_Schedule(the_scheduler); 

      if ( !_Thread_Is_heir( executing ) )
        _Thread_Dispatch_necessary = true;

  _ISR_Enable( level );
}
