/** 
 *  @file  rtems/score/scheduler.inl
 *
 *  This inline file contains all of the inlined routines associated with
 *  the manipulation of the scheduler.
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

/**
 *  This kernel routine implements the scheduling decision logic. It does 
 *  NOT dispatch.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Schedule(
    Scheduler_Control *the_scheduler 
)
{
  the_scheduler->s_ops.schedule( the_scheduler );
}

/**
 *  This routine is invoked when a thread wishes to voluntarily
 *  transfer control of the processor to another thread. This routine
 *  always operates on the scheduler that 'owns' the currently executing
 *  thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Yield( void )
{
  _Scheduler.s_ops.yield( &_Scheduler );
}

/**
 *  This routine removes @a the_thread from the schedulering decision, 
 *  that is, removes it from the ready queue.  It performs
 *  any necessary schedulering operations including the selection of
 *  a new heir thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Block( 
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread 
)
{
  the_scheduler->s_ops.block( the_scheduler, the_thread );
}

/**
 *  This routine adds @a the_thread to the schedulering decision, 
 *  that is, adds it to the ready queue per the schedulering policy and 
 *  updates any appropriate schedulering variables, for example the heir thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Unblock(
    Scheduler_Control *the_scheduler,
    Thread_Control *the_thread 
)
{
  the_scheduler->s_ops.unblock( the_scheduler, the_thread );
}

/**
 * This routine allocates the sched field of @a the_thread
 */
RTEMS_INLINE_ROUTINE void* _Scheduler_Sched_allocate( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
)
{
  return ( the_scheduler->s_ops.sched_allocate( the_scheduler, the_thread ) );
}

/**
 * This routine frees the sched field of @a the_thread
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Sched_free( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
)
{
  return ( the_scheduler->s_ops.sched_free( the_scheduler, the_thread ) );
}

/**
 * This routine updates the sched field of @a the_thread.
 */
RTEMS_INLINE_ROUTINE void _Scheduler_Sched_update( 
  Scheduler_Control *the_scheduler,
  Thread_Control *the_thread
)
{
  the_scheduler->s_ops.sched_update( the_scheduler, the_thread );
}




/**@}*/

#endif
/* end of include file */
