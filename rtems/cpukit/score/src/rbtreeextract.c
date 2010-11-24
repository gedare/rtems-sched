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
 *  _RBTree_Extract
 *
 *  This kernel routine deletes the given node from a rbtree.
 *
 *  Input parameters:
 *    node - pointer to node in rbtree to be deleted
 *
 *  Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 *    only case
 */

void _RBTree_Extract(
  RBTree_Control *the_rbtree,
  RBTree_Node *the_node
)
{
  ISR_Level level;

  _ISR_Disable( level );
    _RBTree_Extract_unprotected( the_rbtree, the_node );
  _ISR_Enable( level );
}
