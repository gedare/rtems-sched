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
#include <rtems/score/priorityrbtree.h>
#include <rtems/score/rbtree.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqedf.h>
#include <rtems/score/states.h>
#include <rtems/score/thread.h>

/*
 *
 *  _Ready_queue_edf_Extract
 *
 *  This routine removes a specific thread from the specified 
 *  edf-based ready queue.
 *
 * If there are other threads with the same 
 * absolute deadline as the_thread, the next one should be added to the 
 * Red-Black Tree.

 *
 *  Input parameters:
 *    the_ready_queue - pointer to a readyq header
 *    the_thread       - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

void _Ready_queue_edf_Extract(
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  Thread_Control  *tmp_thd            = 0;
  RBTree_Node     *tmp_node           = 0;
  Scheduler_edf_Per_thread *tmp_sched = 0;
  Scheduler_edf_Per_thread *sched     = the_thread->sched.edf;

  /* handle aperiodic tasks separately */
  if (!sched->periodic) {
    if (_Chain_Has_only_one_node(&the_ready_queue->Queues.EDF[EDF_APERIODIC]))
      _Chain_Initialize_empty(&the_ready_queue->Queues.EDF[EDF_APERIODIC]);
    else
      _Chain_Extract_unprotected(&the_thread->Object.Node);
    return;
  }

  if ( !(_RBTree_Is_node_off_rbtree( &sched->deadline )) ) {
    _Priority_rbtree_Remove( &sched->deadline );

    if (sched->last_duplicate != &the_thread->Object.Node) {
      tmp_thd = (Thread_Control *) _Chain_Next(&the_thread->Object.Node);
      tmp_sched = tmp_thd->sched.edf;
      /* TODO: remove after debugging */
      if (tmp_sched->deadline.value != sched->deadline.value)
        printk("invalid duplicate\n");

      tmp_sched->last_duplicate = sched->last_duplicate;
      _Priority_rbtree_Add( &tmp_sched->deadline );
      sched->last_duplicate = &the_thread->Object.Node;
    }
  } else {
    /* the_thread is not on the RBTree. Find its duplicate and update 
     * the last_duplicate field if necessary. */
    tmp_node = _RBTree_Find_unprotected(
        &_Priority_RBTree, 
        sched->deadline.value
    );
    if (!tmp_node) {
      /* TODO: remove after debugging */
      printk("invalid thread\n");
      while(1);
    }
    tmp_sched = _RBTree_Container_of(
        tmp_node, 
        Scheduler_edf_Per_thread, 
        deadline
    );
      /* TODO: remove after debugging */
    if (tmp_sched->deadline.value != sched->deadline.value)
      printk("Invalid duplicate\n");

    if (tmp_sched->last_duplicate == &the_thread->Object.Node)
      tmp_sched->last_duplicate = _Chain_Previous(&the_thread->Object.Node);
  }

  if (_Chain_Has_only_one_node( &the_ready_queue->Queues.EDF[EDF_PERIODIC] ))
    _Chain_Initialize_empty( &the_ready_queue->Queues.EDF[EDF_PERIODIC] );
  else
    _Chain_Extract_unprotected( &the_thread->Object.Node );
}

