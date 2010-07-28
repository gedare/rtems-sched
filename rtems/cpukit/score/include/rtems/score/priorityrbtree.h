/**
 *  @file  rtems/score/priorityrbtree.h
 *
 *  This include file contains all thread priority manipulation routines for
 *  the bit map priority queue implementation.
 *  This Handler provides mechanisms which can be used to
 *  initialize and manipulate thread priorities.
 */

/*
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_PRIORITYRBTREE_H
#define _RTEMS_SCORE_PRIORITYRBTREE_H

/**
 *  @addtogroup ScorePriority 
 *  
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/score/rbtree.h>

/* 
 * TODO: This should only be instantiated if using the rbtree handler.
 */

SCORE_EXTERN RBTree_Control _Priority_RBTree;

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/priorityrbtree.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
