/**
 *  @file  rtems/score/rqdata.h
 *
 *  This include file contains all the constants and structures
 *  needed to declare a ready queue.
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

#ifndef _RTEMS_SCORE_RQDATA_H
#define _RTEMS_SCORE_RQDATA_H

/**
 *  @defgroup ScoreReadyQData Ready Queue Handler Data Definition
 *
 *  This handler defines the data shared between the thread and thread
 *  queue handlers.  Having this handler define these data structure
 *  avoids potentially circular references and allows for clean includes 
 *  with limited forward declarations.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/chain.h>
#include <rtems/score/priority.h>

/**
 *  The following enumerated type details all of the disciplines
 *  supported by the Ready Queue Handler.
 */
typedef enum {
  READY_QUEUE_DISCIPLINE_FIFO,     /* FIFO queue discipline */
  READY_QUEUE_DISCIPLINE_PRIORITY  /* PRIORITY queue discipline */
}   Ready_queue_Disciplines;

/**
 *  This is the structure used to manage sets of tasks which are blocked
 *  waiting to acquire a resource.
 */
typedef struct {
  /** This union contains the data structures used to manage the ready
   *  set of tasks which varies based upon the discipline.
   */
  union {
    /** This is the FIFO discipline list. */
    Chain_Control Fifo;

    /** This is the set of lists for priority discipline scheduling. */
    Chain_Control *Priority;
  } Queues;

  /** This field indicates the ready queue's discipline. */
  Ready_queue_Disciplines discipline;
}   Ready_queue_Control;

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/rqdata.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
