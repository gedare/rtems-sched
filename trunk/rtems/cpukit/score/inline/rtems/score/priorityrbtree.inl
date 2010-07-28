/** 
 *  @file  rtems/score/priorityrbtree.inl
 *
 *  This file contains the static inline implementation of all inlined
 *  routines in the Priority Handler red black tree implementation
 */

/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_PRIORITYBITMAP_H
# error "Never use <rtems/score/priorityrbtree.inl> directly; include <rtems/score/priorityrbtree.h> instead."
#endif

#ifndef _RTEMS_SCORE_PRIORITYBITMAP_INL
#define _RTEMS_SCORE_PRIORITYBITMAP_INL

/**
 *  @addtogroup ScorePriority 
 *  @{
 */

/**
 * Priority Queue implemented by red black tree
 */

/**
 * helper functions
 */

/**
 *  This routine performs the initialization necessary for this handler.
 */

RTEMS_INLINE_ROUTINE void _Priority_rbtree_Handler_initialization( void )
{
  _RBTree_Initialize_empty( &_Priority_RBTree );
}

/**
 *  This routine uses the_node to update the priority
 *  red black tree to indicate that a thread has been readied.
 *
 *  If there is already a node on the tree with the same value as the node
 *  being added, this function will return the duplicate node.
 */

RTEMS_INLINE_ROUTINE RBTree_Node* _Priority_rbtree_Add (
  RBTree_Node *the_node
)
{
  return( _RBTree_Insert_unprotected( &_Priority_RBTree, the_node ) );
}

/**
 *  This routine uses the_node to update the priority
 *  red black tree to indicate that a thread has been removed from the
 *  ready state.
 */

RTEMS_INLINE_ROUTINE void _Priority_rbtree_Remove (
  RBTree_Node *the_node
)
{
  _RBTree_Extract_unprotected( &_Priority_RBTree, the_node );
}

/**
 *  This routine initializes @a the_node so that it
 *  contains the information necessary to manage a thread
 *  at @a new_priority.
 *
 *  TODO: is this dead code?
 */

RTEMS_INLINE_ROUTINE void _Priority_rbtree_Initialize_node(
  RBTree_Node                *the_node,
  Priority_Control            new_priority
)
{
  
}

/**@}*/

#endif
/* end of include file */
