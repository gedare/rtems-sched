/** 
 *  @file  rtems/score/scheduler.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of the scheduler.
 */

/*
 *  Copyright (C) 2010 Gedare Bloom.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: scheduler.inl,v 1.2 2010/11/25 13:24:25 sh Exp $
 */

#ifndef _RTEMS_SCORE_SCHEDULER_H
# error "Never use <rtems/score/scheduler.inl> directly; include <rtems/score/scheduler.h> instead."
#endif

#ifndef _RTEMS_SCORE_SCHEDULER_INL
#define _RTEMS_SCORE_SCHEDULER_INL

/**
 *  @addtogroup ScoreScheduler
 * @{
 */

/**
 * The preferred method to add a new scheduler is to define the jump table 
 * entries and add a case to the _Scheduler_Initialize routine. 
 *
 * Generic scheduling implementations that rely on the ready queue only can 
 * be found in the _Scheduler_queue_XXX functions.
 *
 */

/* Passing the Scheduler_Control* to these functions allows for multiple 
 * scheduler's to exist simultaneously, which could be useful on an SMP 
 * system.  Then remote Schedulers may be accessible.  How to protect such 
 * accesses remains an open problem.
 */

/** @brief _Scheduler_Schedule
 *
 *  This kernel routine implements the scheduling decision logic for 
 *  @a the_scheduler. It does NOT dispatch.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Schedule(
    Scheduler_Control *the_scheduler 
)
{
  the_scheduler->Operations.schedule( the_scheduler );
}

/** @brief _Scheduler_Yield
 *
 *  This routine is invoked when a thread wishes to voluntarily
 *  transfer control of the processor to another thread. This routine
 *  always operates on the scheduler that 'owns' the currently executing
 *  thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Yield( void )
{
  _Scheduler.Operations.yield( &_Scheduler );
}

/** @brief _Scheduler_Block
 *
 *  This routine removes @a the_thread from the scheduling decision for 
 *  @a the_scheduler. The primary task is to remove the thread from the 
 *  ready queue.  It performs any necessary schedulering operations 
 *  including the selection of a new heir thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Block( 
    Scheduler_Control *the_scheduler,
    Thread_Control    *the_thread 
)
{
  the_scheduler->Operations.block( the_scheduler, the_thread );
}

/** @brief _Scheduler_Unblock
 *
 *  This routine adds @a the_thread to the scheduling decision for 
 *  @a the_scheduler.  The primary task is to add the thread to the
 *  ready queue per the schedulering policy and update any appropriate 
 *  scheduling variables, for example the heir thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Unblock(
    Scheduler_Control *the_scheduler,
    Thread_Control    *the_thread 
)
{
  the_scheduler->Operations.unblock( the_scheduler, the_thread );
}

/** @brief _Scheduler_Thread_scheduler_allocate
 *
 * This routine allocates @a the_thread->scheduler
 */
RTEMS_INLINE_ROUTINE void* _Scheduler_Thread_scheduler_allocate( 
  Scheduler_Control *the_scheduler,
  Thread_Control    *the_thread
)
{
  return 
    the_scheduler->Operations.scheduler_allocate( the_scheduler, the_thread );
}

/** @brief _Scheduler_Thread_scheduler_free
 *
 * This routine frees @a the_thread->scheduler
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Thread_scheduler_free( 
  Scheduler_Control *the_scheduler,
  Thread_Control    *the_thread
)
{
  return the_scheduler->Operations.scheduler_free( the_scheduler, the_thread );
}

/** @brief _Scheduler_Thread_scheduler_update
 *
 * This routine updates @a the_thread->scheduler
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Thread_scheduler_update( 
  Scheduler_Control *the_scheduler,
  Thread_Control    *the_thread
)
{
  the_scheduler->Operations.scheduler_update( the_scheduler, the_thread );
}

/**@}*/

#endif
/* end of include file */
