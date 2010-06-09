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
 *  _Ready_queue_Extract_priority
 *
 *  This routine removes a specific thread from the specified readyq
 *
 *  Input parameters:
 *    the_ready_queue - pointer to a readyq header
 *    the_thread       - pointer to a thread control block
 *    requeuing        - true if requeuing and should not alter timeout or state
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 *    EXTRACT_PRIORITY
 */

void _Ready_queue_Extract_priority_helper(
  Ready_queue_Control *the_ready_queue __attribute__((unused)),
  Thread_Control       *the_thread,
  bool                  requeuing
)
{

  Chain_Control *ready = the_thread->ready;

  if ( _Chain_Has_only_one_node( ready ) ) {

    _Chain_Initialize_empty( ready );
    _Priority_Remove( &the_thread->Priority_map );

  } else
    _Chain_Extract_unprotected( &the_thread->Object.Node );
  
  /*
   *  If we are not supposed to touch timers or the thread's state, return.
   */

  if ( requeuing ) {
    return;
  }

#if 0
  if ( !_Watchdog_Is_active( &the_thread->Timer ) ) {
    _ISR_Enable( level );
  } else {
    _Watchdog_Deactivate( &the_thread->Timer );
    _ISR_Enable( level );
    (void) _Watchdog_Remove( &the_thread->Timer );
  }
#endif

#if 0
#if defined(RTEMS_MULTIPROCESSING)
  if ( !_Objects_Is_local_id( the_thread->Object.id ) )
    _Thread_MP_Free_proxy( the_thread );
#endif
#endif
}
