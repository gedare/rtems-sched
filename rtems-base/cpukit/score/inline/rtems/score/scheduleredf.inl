/** 
 *  @file  rtems/score/scheduleredf.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of the edf-based scheduling structures.
 */

/*
 *  Copyright (C) 2010 Gedare Bloom.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_SCHEDULEREDF_H
# error "Never use <rtems/score/scheduleredf.inl> directly; include <rtems/score/scheduleredf.h> instead."
#endif

#ifndef _RTEMS_SCORE_SCHEDULEREDF_INL
#define _RTEMS_SCORE_SCHEDULEREDF_INL

/**
 *  @addtogroup ScoreScheduler
 * @{
 */

/** @brief  Scheduler edf Ready queue initialize
 *
 *  This routine initializes edf-based scheduling.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_edf_Ready_queue_initialize(
  Scheduler_Control         *the_scheduler
) {
  /* allocate ready queue structures */
  the_scheduler->Ready_queues.edf = (Scheduler_edf_Ready_queue_Control *) 
    _Workspace_Allocate_or_fatal_error(
        (1) * sizeof(Scheduler_edf_Ready_queue_Control)
    );

  /* initialize ready queue structures */
  _Chain_Initialize_empty( &the_scheduler->Ready_queues.edf->deadline_queue );
  _Chain_Initialize_empty( &the_scheduler->Ready_queues.edf->fifo_queue );
  _RBTree_Initialize_empty( &the_scheduler->Ready_queues.edf->edf_rbtree );
}

/* 
 *  _Scheduler_edf_Ready_queue_enqueue
 *
 *  This routine puts @a the_thread on to the edf-based ready queue.
 *  
 *  Input parameters:
 *    the_thread  - pointer to thread
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Ready_queue_enqueue(
  Thread_Control                  *the_thread
)
{
  RBTree_Node *tmp_node = NULL;
  Scheduler_edf_Per_thread *sched = the_thread->scheduler.edf;
  Scheduler_edf_Per_thread *tmp_sched = NULL;
  Chain_Control *fifo = NULL;
  /* FIXME: shouldn't refer to the global _Scheduler directly */
  Scheduler_Control *the_scheduler = &_Scheduler;

  /*
   * This function adds the_thread to its proper location in the 
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
   */

  /* queue tasks without deadlines separately */
  if (!sched->deadline.value) {
    fifo = &the_scheduler->Ready_queues.edf->fifo_queue;
    _Chain_Append_unprotected( fifo, &the_thread->Object.Node );
    if ( the_thread != _Thread_Idle && 
        _Chain_First(fifo) == &_Thread_Idle->Object.Node ) {
      _Chain_Extract_unprotected( &_Thread_Idle->Object.Node );
      _Chain_Append_unprotected( fifo, &_Thread_Idle->Object.Node );
    }
    return;
  }

  /* first add the_thread to red-black tree */
  tmp_node = _RBTree_Insert_unprotected(
               &the_scheduler->Ready_queues.edf->edf_rbtree, 
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

  if (_RBTree_Is_root(
        &the_scheduler->Ready_queues.edf->edf_rbtree,
        &sched->deadline
    )) { /* 4 */
    _Chain_Append_unprotected( 
        &the_scheduler->Ready_queues.edf->deadline_queue, 
        &the_thread->Object.Node
    );
    return;
  }  

  tmp_node = _RBTree_Parent( &sched->deadline );
  tmp_sched = _RBTree_Container_of(tmp_node, 
      Scheduler_edf_Per_thread, 
      deadline
  );

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

/*
 *  _Scheduler_edf_Ready_queue_Enqueue_first
 *
 *  This routine puts @a the_thread to the head of the ready queue. 
 *  For edf-based ready queues, the thread will be the first thread
 *  at its edf level.
 *  
 *  Input parameters:
 *    the_thread      - pointer to thread
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY:
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Ready_queue_enqueue_first(
  Thread_Control                   *the_thread
)
{
  Scheduler_edf_Per_thread *sched = the_thread->scheduler.edf;
  /* FIXME: Shouldn't reference _Scheduler */
  Scheduler_Control *the_scheduler = &_Scheduler;

  /* treat non-periodic tasks */
  if (!sched->deadline.value) {
    _Chain_Prepend_unprotected(
        &the_scheduler->Ready_queues.edf->fifo_queue,
        &the_thread->Object.Node
    );
    return;
  }

  /* TODO: re-write periodic tasks enqueue with lifo to break deadline ties? */
  _Scheduler_edf_Ready_queue_enqueue(the_thread);
  return;
}

/*
 *  _Scheduler_edf_Ready_queue_extract
 *
 *  This routine removes a specific thread from the specified 
 *  edf-based ready queue.
 *
 *  Input parameters:
 *    the_thread       - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Ready_queue_extract(
  Thread_Control        *the_thread
)
{
  Thread_Control  *tmp_thd            = 0;
  RBTree_Node     *tmp_node           = 0;
  Scheduler_edf_Per_thread *tmp_sched = 0;
  Scheduler_edf_Per_thread *sched     = the_thread->scheduler.edf;

  /* FIXME: Shouldn't reference _Scheduler */
  Scheduler_Control *the_scheduler = &_Scheduler;

  /* handle tasks without a deadline separately */
  if (!sched->deadline.value) {
    if (_Chain_Has_only_one_node(&the_scheduler->Ready_queues.edf->fifo_queue))
      _Chain_Initialize_empty(&the_scheduler->Ready_queues.edf->fifo_queue);
    else
      _Chain_Extract_unprotected(&the_thread->Object.Node);
    return;
  }

  if ( !(_RBTree_Is_node_off_rbtree( &sched->deadline )) ) {
    _RBTree_Extract_unprotected(
        &the_scheduler->Ready_queues.edf->edf_rbtree,
        &sched->deadline
    );

    if (sched->last_duplicate != &the_thread->Object.Node) {
      tmp_thd = (Thread_Control *) _Chain_Next(&the_thread->Object.Node);
      tmp_sched = tmp_thd->scheduler.edf;
      /* TODO: remove after debugging */
      if (tmp_sched->deadline.value != sched->deadline.value)
        printk("invalid duplicate\n");

      tmp_sched->last_duplicate = sched->last_duplicate;
      _RBTree_Insert_unprotected(
          &the_scheduler->Ready_queues.edf->edf_rbtree,
          &tmp_sched->deadline
      );
      sched->last_duplicate = &the_thread->Object.Node;
    }
  } else {
    /* the_thread is not on the RBTree. Find its duplicate and update 
     * the last_duplicate field if necessary. */
    tmp_node = _RBTree_Find_unprotected(
        &the_scheduler->Ready_queues.edf->edf_rbtree, 
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

  if (_Chain_Has_only_one_node(
        &the_scheduler->Ready_queues.edf->deadline_queue
      ))
    _Chain_Initialize_empty( &the_scheduler->Ready_queues.edf->deadline_queue );
  else
    _Chain_Extract_unprotected( &the_thread->Object.Node );
}

/*
 *  _Scheduler_edf_Ready_queue_first
 *
 *  This routines returns a pointer to the first thread on @a the_ready_queue.
 *
 *  Input parameters:
 *    the_ready_queue - pointer to thread queue
 *
 *  Output parameters:
 *    returns - first thread or NULL
 */

RTEMS_INLINE_ROUTINE Thread_Control *_Scheduler_edf_Ready_queue_first(
  Scheduler_Control       *the_scheduler
)
{
  /* when there are periodic jobs to run, schedule them first */
  if ( !_Chain_Is_empty(&the_scheduler->Ready_queues.edf->deadline_queue ) )
    return (Thread_Control *) 
      _Chain_First(&the_scheduler->Ready_queues.edf->deadline_queue);

  /* otherwise schedule aperiodic jobs as background tasks */

  /* If idle is going to be heir, re-queue it. */
  if ( _Chain_First(&the_scheduler->Ready_queues.edf->fifo_queue) == 
        &_Thread_Idle->Object.Node ) {
    _Scheduler_edf_Ready_queue_extract( _Thread_Idle ); 
    _Scheduler_edf_Ready_queue_enqueue( _Thread_Idle );
  }

  /* this is the idle thread if there are no other aperiodic jobs */
  return (Thread_Control *) 
    _Chain_First(&the_scheduler->Ready_queues.edf->fifo_queue);
}

/*
 *  _Scheduler_edf_Ready_queue_requeue
 *
 *  This routine is invoked when a thread changes edf and should be
 *  moved to a different position on the ready queue.
 *
 *  Input parameters:
 *    the_thread        - pointer to a thread control block
 *
 *  Output parameters: NONE
 *
 *  INTERRUPT LATENCY: NONE
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Ready_queue_requeue(
  Thread_Control            *the_thread
)
{
 /* TODO: can implement requeueing non-periodic tasks, and cycling through
  * tasks that have identical deadline */
  _Scheduler_edf_Ready_queue_extract(the_thread);
  _Scheduler_edf_Ready_queue_enqueue(the_thread);
}

/*
 * _Scheduler_edf_Schedule_body
 *
 * This kernel routine implements scheduling decision logic for edf-based
 * scheduling.  
 *
 * Input parameters:
 *   the_scheduler  - pointer to scheduler control
 *   the_thread     - pointer to thread control block
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Schedule_body(
  Scheduler_Control     *the_scheduler
)
{
  _Thread_Heir = _Scheduler_edf_Ready_queue_first(the_scheduler);
}

/*
 * _Scheduler_edf_Block_body
 *
 * This kernel routine removes the_thread from scheduling decisions based 
 * on simple queue extraction.
 *
 * Input parameters:
 *   the_scheduler  - pointer to scheduler control
 *   the_thread     - pointer to thread control block
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Block_body(
  Scheduler_Control *the_scheduler,
  Thread_Control   *the_thread
)
{
  _Scheduler_edf_Ready_queue_extract(the_thread);

  /* TODO: flash critical section */

  if ( _Thread_Is_heir( the_thread ) )
     _Scheduler_edf_Schedule_body(the_scheduler);

  if ( _Thread_Is_executing( the_thread ) )
    _Thread_Dispatch_necessary = true;

  return;
}

/*
 *  _Scheduler_edf_Unblock_body
 *
 *  This kernel routine readies the requested thread according to the queuing 
 *  discipline. A new heir thread may be selected.
 *
 *  Input parameters:
 *    the_scheduler - pointer to scheduler control
 *    the_thread    - pointer to thread control block
 *
 *  Output parameters:  NONE
 *
 *  NOTE:  This routine uses the "blocking" heir selection mechanism.
 *         This ensures the correct heir after a thread restart.
 *
 *  INTERRUPT LATENCY:
 */

RTEMS_INLINE_ROUTINE void _Scheduler_edf_Unblock_body (
  Scheduler_Control       *the_scheduler,
  Thread_Control          *the_thread
)
{
  _Scheduler_edf_Ready_queue_enqueue(
      the_thread
  );

  /* TODO: flash critical section */

  /* TODO: can this be short-circuited like in priority scheduling? */
  _Scheduler_edf_Schedule_body(the_scheduler);

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
  if ( !_Thread_Is_executing( _Thread_Heir ) ) {
    if ( _Thread_Executing->is_preemptible || 
         the_thread->current_priority == 0 )
      _Thread_Dispatch_necessary = true;
  }
}

/**@}*/

#endif
/* end of include file */
