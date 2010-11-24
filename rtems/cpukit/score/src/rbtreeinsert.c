/*
 *  Copyright (c) 2010 Gedare Bloom.
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
#include <rtems/score/address.h>
#include <rtems/score/rbtree.h>
#include <rtems/score/isr.h>

/*
 *  _RBTree_Insert
 *
 *  This kernel routine inserts a given node after a specified node
 *  a requested rbtree.
 *
 *  Input parameters:
 *    tree - pointer to RBTree Control for tree to insert to
 *    node       - pointer to node to be inserted
 *
 *  Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 *    only case
 */

void _RBTree_Insert(
  RBTree_Control *tree,
  RBTree_Node *node
)
{
  ISR_Level level;

  _ISR_Disable( level );
    _RBTree_Insert_unprotected( tree, node );
  _ISR_Enable( level );
}
