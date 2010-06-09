/** 
 *  @file  rtems/score/readyq.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of ready queues.
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_READYQ_H
# error "Never use <rtems/score/readyq.inl> directly; include <rtems/score/readyq.h> instead."
#endif

#ifndef _RTEMS_SCORE_READYQ_INL
#define _RTEMS_SCORE_READYQ_INL

#include <rtems/score/thread.h>

/**
 *  @addtogroup ScoreReadyQ
 * @{
 */


/*
 *  _Ready_queue_Dequeue_priority
 *
 *  This routine returns a thread from the PRIORITY based @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_Dequeue_priority(
  Ready_queue_Control *the_ready_queue
)
{
  uint32_t        index;
  Chain_Control *rq;
  Thread_Control *the_thread;

  index = _Priority_Get_value(_Priority_Get_highest());
  rq = &_Thread_Ready_queue.Queues.Priority[index];
  the_thread = (Thread_Control*) _Chain_First(rq);
  
  if ( _Chain_Has_only_one_node( rq ) ) {
    _Chain_Initialize_empty( rq );
    _Priority_Remove( &the_thread->Priority_map );
  } else
    _Chain_Extract_unprotected( &the_thread->Object.Node );
 
  return 0;
}

/*
 *  _Ready_queue_Dequeue_fifo
 *
 *  This routine returns a thread from @a the_ready_queue
 *
 */

RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_Dequeue_fifo(
  Ready_queue_Control *the_ready_queue
)
{
  Thread_Control *the_thread;

  if ( !_Chain_Is_empty( &the_ready_queue->Queues.Fifo ) ) {

    the_thread = (Thread_Control *)
       _Chain_Get_first_unprotected( &the_ready_queue->Queues.Fifo );

    return the_thread;
  }

  return NULL;
}

/*
 *  _Ready_queue_Enqueue_fifo
 *
 *  This routine places @a the_thread on a FIFO @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue_fifo (
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  _Chain_Append_unprotected(
        &the_ready_queue->Queues.Fifo,
        &the_thread->Object.Node
      );
  the_thread->ready = &the_ready_queue->Queues.Fifo;
}

/*
 *  _Ready_queue_Enqueue_priority
 *
 *  @brief This routine places a @a the_thread on @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue_priority (
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  _Priority_Add( &the_thread->Priority_map );
  _Chain_Append_unprotected( the_thread->ready, &the_thread->Object.Node );
}

/*
 *  _Ready_queue_Enqueue_first_fifo
 *
 *  This routine places the ready @a the_thread to the head of the 
 *  FIFO @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue_first_fifo (
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  _Chain_Prepend_unprotected(
        &the_ready_queue->Queues.Fifo,
        &the_thread->Object.Node
      );
}

/*
 *  _Ready_queue_Enqueue_first_priority
 *
 *  This routine places the ready @a the_thread to the head of the
 *  priority @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Enqueue_first_priority (
  Ready_queue_Control *the_ready_queue,
  Thread_Control       *the_thread
)
{
  _Priority_Add( &the_thread->Priority_map );
  _Chain_Prepend_unprotected( the_thread->ready, &the_thread->Object.Node );
}

/*
 *  _Ready_queue_Extract_fifo
 *
 *  This routine removes @a the_thread from @a the_ready_queue
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Extract_fifo(
  Ready_queue_Control *the_ready_queue __attribute__((unused)),
  Thread_Control       *the_thread
)
{
  _Chain_Extract_unprotected( &the_thread->Object.Node );

  /* 
   * this is leftover from the threadq code, but might be useful for 
   * implementing periodic timers.
   */
#if 0
  if ( !_Watchdog_Is_active( &the_thread->Timer ) ) {
    _ISR_Enable( level );
  } else {
    _Watchdog_Deactivate( &the_thread->Timer );
    _ISR_Enable( level );
    (void) _Watchdog_Remove( &the_thread->Timer );
  }

#if defined(RTEMS_MULTIPROCESSING)
  if ( !_Objects_Is_local_id( the_thread->Object.id ) )
    _Thread_MP_Free_proxy( the_thread );
#endif
#endif
}

/*
 *  _Ready_queue_Extract_priority_helper
 *
 *  This routine removes @a the_thread from @a the_ready_queue
 *
 */

RTEMS_INLINE_ROUTINE void _Ready_queue_Extract_priority_helper(
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

#if defined(RTEMS_MULTIPROCESSING)
  if ( !_Objects_Is_local_id( the_thread->Object.id ) )
    _Thread_MP_Free_proxy( the_thread );
#endif
#endif
}

/*
 *  _Ready_queue_Extract_with_proxy
 *
 *  This routine extracts the_thread from the_ready_queue
 *  and ensures that if there is a proxy for this task on
 *  another node, it is also dealt with.
 *
 *  XXX
 */

RTEMS_INLINE_ROUTINE bool _Ready_queue_Extract_with_proxy(
  Thread_Control       *the_thread
)
{
  return false;
}

/*
 *  _Ready_queue_First_fifo
 *
 *  This routines returns a pointer to the first thread on 
 *  @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_First_fifo(
  Ready_queue_Control *the_ready_queue
)
{
  if ( !_Chain_Is_empty( &the_ready_queue->Queues.Fifo ) )
    return (Thread_Control *) the_ready_queue->Queues.Fifo.first;

  return NULL;
}

/*
 *  _Ready_queue_First_priority
 *
 *  This routines returns a pointer to the first thread on 
 *  @a the_ready_queue.
 *
 */

RTEMS_INLINE_ROUTINE Thread_Control *_Ready_queue_First_priority (
  Ready_queue_Control *the_ready_queue
)
{
  uint32_t   index = _Priority_Get_highest();

  if ( !_Chain_Is_empty( &the_ready_queue->Queues.Priority[ index ] ) )
    return (Thread_Control *) the_ready_queue->Queues.Priority[ index ].first;

  return NULL;
}



/**@}*/

#endif
/* end of include file */
