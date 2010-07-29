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
#include <rtems/score/states.h>
#include <rtems/score/thread.h>
#include <rtems/score/rbtree.h>
#include <rtems/score/readyq.h>
#include <rtems/score/readyqedf.h>

/* 
 *  _Ready_queue_edf_Enqueue
 *
 * This function adds the thread @a the_thread to its proper location in the 
 * Red-Black Tree, and then determines where to place it in the ready queue. 
 * There are 6 cases:
 *    1) There is already a thread with the same absolute deadline. 
 *       Add the new thread after threads in the list with the same deadline.
 *    2) The new thread has an in-order predecessor in the RBTree. 
 *       Add the new thread after its predecessor (check for duplicates).
 *    3) The new thread has an in-order successor in the RBTree.
 *       Add the new thread before its successor.
 *    4) The new thread is the only thread in the tree.
 *    5) The new thread is to the left of its parent in the RBTree.
 *       Add the new thread before its parent.
 *    6) The new thread is to the right of its parent in the RBTree.
 *       Add the new thread after its parent (check for duplicates).
 *
 * Assume that the value of the_thread->sched.edf->deadline.value has already
 * been set to the thread's absolute deadline.
 *  
 *  Input parameters:
 *    the_ready_queue - pointer to readyq
 *    the_thread  - pointer to thread
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Ready_queue_edf_Enqueue(
  Ready_queue_Control         *the_ready_queue,
  Thread_Control                   *the_thread
)
{
  RBTree_Node *tmp_node = 0;

  Scheduler_edf_Per_thread *sched = the_thread->sched.edf;
  Scheduler_edf_Per_thread *tmp_sched;

  /* queue tasks without deadlines separately */
  if (!sched->deadline.value) {
    _Chain_Append_unprotected(
        &the_ready_queue->Queues.EDF->fifo_queue, 
        &the_thread->Object.Node
    );
    return;
  }

  /* first add the_thread to red-black tree */
  tmp_node = _RBTree_Insert_unprotected(
               &_Ready_queue_edf_RBTree, 
               &sched->deadline
             );
  if (tmp_node) { /* 1 */
    tmp_sched = _RBTree_Container_of(
        tmp_node, 
        Scheduler_edf_Per_thread, 
        deadline
    );
    _Chain_Insert_unprotected(
        tmp_sched->last_duplicate, 
        &the_thread->Object.Node
    );
    tmp_sched->last_duplicate = &the_thread->Object.Node;
    return;
  }

  tmp_node = _RBTree_Predecessor( &sched->deadline );

  if (tmp_node) { /* 2 */
    tmp_sched = _RBTree_Container_of(
        tmp_node, 
        Scheduler_edf_Per_thread, 
        deadline
    );
    _Chain_Insert_unprotected(
        tmp_sched->last_duplicate,
        &the_thread->Object.Node
    );
    return;
  }

  tmp_node = _RBTree_Successor( &sched->deadline );

  if (tmp_node) { /* 3 */
    tmp_sched = _RBTree_Container_of(
        tmp_node, 
        Scheduler_edf_Per_thread, 
        deadline
    );
    _Chain_Insert_unprotected(
        _Chain_Previous(&tmp_sched->this_thread->Object.Node), 
        &the_thread->Object.Node
    );
    return;
  } 

  tmp_node = _RBTree_Parent( &sched->deadline );

  tmp_sched = _RBTree_Container_of(tmp_node, 
      Scheduler_edf_Per_thread, 
      deadline
  );

  if (_RBTree_Is_root(
        &_Ready_queue_edf_RBTree,
        &tmp_sched->deadline
    )) { /* 4 */
    _Chain_Append_unprotected( 
        &the_ready_queue->Queues.EDF->deadline_queue, 
        &the_thread->Object.Node
    );
    return;
  }  
  
  if ( _RBTree_Are_nodes_equal(&sched->deadline, 
        _RBTree_Left(tmp_node))) { /* 5 */
    _Chain_Insert_unprotected(
        _Chain_Previous(&tmp_sched->this_thread->Object.Node), 
        &the_thread->Object.Node
    );
    return;
  } 
  
  /* 6 */
  _Chain_Insert_unprotected(
      tmp_sched->last_duplicate,
      &the_thread->Object.Node
  );

}
