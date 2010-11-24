/**
 *  @file  rtems/score/rbtree.inl
 *
 *  This include file contains the bodies of the routines which are
 *  associated with Red-Black Trees and inlined.
 *
 *  @note  The routines in this file are ordered from simple
 *         to complex.  No other RBTree Handler routine is referenced
 *         unless it has already been defined.
 */

/*
 *  Copyright (c) 2010 Gedare Bloom.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_RBTREE_H
# error "Never use <rtems/score/rbtree.inl> directly; include <rtems/score/rbtree.h> instead."
#endif

#ifndef _RTEMS_SCORE_RBTREE_INL
#define _RTEMS_SCORE_RBTREE_INL

/**
 *  @addtogroup ScoreRBTree 
 *  @{
 */

/** @brief Set off rbtree
 *
 *  This function sets the parent and child fields of the @a node to NULL
 *  indicating the @a node is not part of a rbtree.
 *
 */
RTEMS_INLINE_ROUTINE void _RBTree_Set_off_rbtree(
    RBTree_Node *node
    )
{
  node->parent = node->child[RBT_LEFT] = node->child[RBT_RIGHT] = NULL;
}

/** @brief Is the Node off RBTree
 *
 *  This function returns true if the @a node is not on a rbtree. A @a node is
 *  off rbtree if the parent and child fields are set to NULL.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_node_off_rbtree(
    const RBTree_Node *node
    )
{
  return (node->parent == NULL) && (node->child[RBT_LEFT] == NULL) && (node->child[RBT_RIGHT] == NULL);
}

/** @brief Are Two Nodes Equal
 *
 *  This function returns true if @a left and @a right are equal,
 *  and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Are_nodes_equal(
    const RBTree_Node *left,
    const RBTree_Node *right
    )
{
  return left == right;
}

/** @brief Is this RBTree Control Pointer Null
 *
 *  This function returns true if @a the_rbtree is NULL and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_null(
    const RBTree_Control *the_rbtree
    )
{
  return (the_rbtree == NULL);
}

/** @brief Is the RBTree Node Pointer NULL
 *
 *  This function returns true if @a the_node is NULL and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_null_node(
    const RBTree_Node *the_node
    )
{
  return (the_node == NULL);
}


/** @brief Return pointer to RBTree's root node
 *
 *  This function returns a pointer to the root node of @a the_rbtree.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Root(
    RBTree_Control *the_rbtree
    )
{
  return the_rbtree->root;
}

/** @brief Return pointer to RBTree's First node
 *
 *  This function returns a pointer to the first node on @a the_rbtree, 
 *  where @a dir specifies whether to return the minimum (0) or maximum (1).
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_First(
    RBTree_Control *the_rbtree,
    RBTree_Direction dir
    )
{
  return the_rbtree->first[dir];
}

/** @brief Return pointer to the parent of this node
 *
 *  This function returns a pointer to the parent node of @a the_node.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Parent(
    RBTree_Node *the_node
    )
{
  if (!the_node->parent->parent) return NULL;
  return the_node->parent;
}

/** @brief Return pointer to the left of this node
 *
 *  This function returns a pointer to the left node of this node.
 *
 *  @param[in] the_node is the node to be operated upon.
 *
 *  @return This method returns the left node on the rbtree.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Left(
    RBTree_Node *the_node
    )
{
  return the_node->child[RBT_LEFT];
}

/** @brief Return pointer to the right of this node
 *
 *  This function returns a pointer to the right node of this node.
 *
 *  @param[in] the_node is the node to be operated upon.
 *
 *  @return This method returns the right node on the rbtree.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Right(
    RBTree_Node *the_node
    )
{
  return the_node->child[RBT_RIGHT];
}

/** @brief Is the RBTree Empty
 *
 *  This function returns true if there are no nodes on @a the_rbtree and
 *  false otherwise.
 *
 *  @param[in] the_rbtree is the rbtree to be operated upon.
 *
 *  @return This function returns true if there are no nodes on 
 *  @a the_rbtree and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_empty(
    RBTree_Control *the_rbtree
    )
{
  return (the_rbtree->root == NULL);
}

/** @brief Is this the First Node on the RBTree
 *
 *  This function returns true if @a the_node is the first node on 
 *  @a the_rbtree and false otherwise. @a dir specifies whether first means 
 *  minimum (0) or maximum (1).
 *
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_first(
    RBTree_Control *the_rbtree,
    const RBTree_Node *the_node,
    RBTree_Direction dir
    )
{
  return (the_node == _RBTree_First(the_rbtree, dir));
}

/** @brief Is this node red?
 *
 *  This function returns true if @a the_node is red and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_red(
    const RBTree_Node *the_node
    )
{
  return (the_node && the_node->color == RBT_RED);
}


/** @brief Does this RBTree have only One Node
 *
 *  This function returns true if there is only one node on @a the_rbtree and
 *  false otherwise.
 *
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Has_only_one_node(
    const RBTree_Control *the_rbtree
    )
{
  if(!the_rbtree) return NULL; /* TODO: expected behavior? */
  return (the_rbtree->root->child[RBT_LEFT] == NULL && the_rbtree->root->child[RBT_RIGHT] == NULL);
}

/** @brief Is this Node the RBTree root
 *
 *  This function returns true if @a the_node is the root of @a the_rbtree and
 *  false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _RBTree_Is_root(
    RBTree_Control *the_rbtree,
    const RBTree_Node    *the_node
    )
{
  return (the_node == _RBTree_Root(the_rbtree));
}

/** @brief Initialize this RBTree as Empty
 *
 *  This routine initializes @a the_rbtree to contain zero nodes.
 */
RTEMS_INLINE_ROUTINE void _RBTree_Initialize_empty(
    RBTree_Control *the_rbtree
    )
{
  the_rbtree->permanent_null = NULL;
  the_rbtree->root           = NULL;
  the_rbtree->first[0]       = NULL;
  the_rbtree->first[1]       = NULL;
}

/** @brief Return a pointer to node's grandparent
 *
 *  This function returns a pointer to the grandparent of @a the_node if it 
 *  exists, and NULL if not. 
 *  
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Grandparent(
    RBTree_Node *the_node
    )
{
  if(!the_node) return NULL;
  if(!(the_node->parent)) return NULL;
  if(!(the_node->parent->parent)) return NULL;
  if(!(the_node->parent->parent->parent)) return NULL;
  return(the_node->parent->parent);
}

/** @brief Return a pointer to node's sibling
 *
 *  This function returns a pointer to the sibling of @a the_node if it 
 *  exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Sibling(
    RBTree_Node *the_node
    )
{
  if(!the_node) return NULL;
  if(!(the_node->parent)) return NULL;
  if(!(the_node->parent->parent)) return NULL;

  if(the_node == the_node->parent->child[RBT_LEFT])
    return the_node->parent->child[RBT_RIGHT];
  else
    return the_node->parent->child[RBT_LEFT];
}

/** @brief Return a pointer to node's parent's sibling
 *
 *  This function returns a pointer to the sibling of the parent of 
 *  @a the_node if it exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Parent_sibling(
    RBTree_Node *the_node
    )
{
  if(!the_node) return NULL;
  if(_RBTree_Grandparent(the_node) == NULL) return NULL;

  return _RBTree_Sibling(the_node->parent);
}

/** @brief Find the RBTree_Control header given a node in the tree
 *
 *  This function returns a pointer to the header of the Red Black 
 *  Tree containing @a the_node if it exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Control *_RBTree_Find_header_unprotected(
    RBTree_Node *the_node
    )
{
  if(!the_node) return NULL;
  if(!(the_node->parent)) return NULL;
  while(the_node->parent) the_node = the_node->parent;
  return (RBTree_Control*)the_node;
}

/** @brief Find the node with given value in the tree
 *
 *  This function returns a pointer to the node in @a the_rbtree 
 *  having value equal to @a the_value if it exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Find_unprotected(
    RBTree_Control *the_rbtree,
    unsigned int the_value
    )
{
  RBTree_Node* iter_node = the_rbtree->root;
  while (iter_node) {
    if (the_value == iter_node->value) return(iter_node);

    RBTree_Direction dir = the_value > iter_node->value;
    iter_node = iter_node->child[dir];
  } /* while(iter_node) */

  return 0;
}

/** @brief Find the nodes in-order predecessor
 *
 *  This function returns a pointer to the in-order predecessor 
 *  of @a the_node if it exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Predecessor(
    RBTree_Node *the_node
    )
{
  if (!the_node) return NULL;
  RBTree_Node* iter_node = the_node->child[RBT_LEFT];
  if (!iter_node) return NULL;
  while (iter_node->child[RBT_RIGHT]) {
    iter_node = iter_node->child[RBT_RIGHT];
  } 
  return iter_node;
}

/** @brief Find the nodes in-order successor
 *
 *  This function returns a pointer to the in-order successor  
 *  of @a the_node if it exists, and NULL if not. 
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Successor(
    RBTree_Node *the_node
    )
{
  if (!the_node) return NULL;
  RBTree_Node* iter_node = the_node->child[RBT_RIGHT];
  if (!iter_node) return NULL;
  while (iter_node->child[RBT_LEFT]) {
    iter_node = iter_node->child[RBT_LEFT];
  } 
  return iter_node;
}


/** @brief Peek at the First Node (unprotected)
 *
 *  This function returns a pointer to the first node, minimum if @a dir is 0 
 *  or maximum if @a dir is 1, from @a the_rbtree without extracting it.  
 *  It does NOT disable interrupts to ensure the atomicity of the peek.
 *
 *  @retval NULL if @a the_rbtree is empty.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Peek_unprotected(
    RBTree_Control *the_rbtree,
    RBTree_Direction dir
    )
{
  return(the_rbtree->first[dir]);
}

/** @brief Rotate the_node in the direction passed as second argument
 *  
 *  This routine rotates @a the_node to the direction @a dir, swapping
 *  @a the_node with its child\[@a dir\].
 */
RTEMS_INLINE_ROUTINE void _RBTree_Rotate(
    RBTree_Node *the_node,
    RBTree_Direction dir
    )
{
  RBTree_Node *c;
  if (the_node == NULL) return;
  if (the_node->child[(1-dir)] == NULL) return;
  

  c = the_node->child[(1-dir)];
  the_node->child[(1-dir)] = c->child[dir];

  if (c->child[dir])
    c->child[dir]->parent = the_node;

  c->child[dir] = the_node;

  the_node->parent->child[the_node != the_node->parent->child[0]] = c;

  c->parent = the_node->parent;
  the_node->parent = c;
}
/**@}*/

/** @brief Validate and fix-up tree properties for a new insert/colored node
 *
 *  This routine checks and fixes the Red-Black Tree properties based on 
 *  @a the_node being just added to the tree.
 * 
 *  @note It does NOT disable interrupts to ensure the atomicity of the
 *        append operation.
 */
RTEMS_INLINE_ROUTINE void _RBTree_Validate_insert_unprotected(
    RBTree_Node    *the_node
    )
{
  RBTree_Node *u,*g;

  /* note: the insert root case is handled already */
  /* if the parent is black, nothing needs to be done
   * otherwise may need to loop a few times */
  while (_RBTree_Is_red(_RBTree_Parent(the_node))) {
    u = _RBTree_Parent_sibling(the_node);
    g = the_node->parent->parent;
    
    /* if uncle is red, repaint uncle/parent black and grandparent red */
    if(_RBTree_Is_red(u)) {
      the_node->parent->color = RBT_BLACK;
      u->color = RBT_BLACK;
      g->color = RBT_RED;
      the_node = g;
    } else { /* if uncle is black */
      RBTree_Direction dir = the_node != the_node->parent->child[0];
      RBTree_Direction pdir = the_node->parent != g->child[0];
      
      /* ensure node is on the same branch direction as parent */
      if (dir != pdir) {
        _RBTree_Rotate(the_node->parent, pdir);
        the_node = the_node->child[pdir];
      }
      the_node->parent->color = RBT_BLACK;
      g->color = RBT_RED;
      
      /* now rotate grandparent in the other branch direction (toward uncle) */
      _RBTree_Rotate(g, (1-pdir));
    }
  }
  if(!the_node->parent->parent) the_node->color = RBT_BLACK;
}

/** @brief Insert a Node (unprotected)
 *
 *  This routine inserts @a the_node on the Red-Black Tree @a the_rbtree.
 *
 *  @retval 0 Successfully inserted.
 *  @retval -1 NULL @a the_node.
 *  @retval RBTree_Node* if one with equal value to @a the_node->value exists 
 *          in @a the_rbtree.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity
 *        of the extract operation.
 */
RTEMS_INLINE_ROUTINE  RBTree_Node *_RBTree_Insert_unprotected(
    RBTree_Control *the_rbtree,
    RBTree_Node *the_node
    )
{
  if(!the_node) return (RBTree_Node*)-1;

  RBTree_Node *iter_node = the_rbtree->root;

  if (!iter_node) { /* special case: first node inserted */
    the_node->color = RBT_BLACK;
    the_rbtree->root = the_node;
    the_rbtree->first[0] = the_rbtree->first[1] = the_node;
    the_node->parent = (RBTree_Node *) the_rbtree;
    the_node->child[RBT_LEFT] = the_node->child[RBT_RIGHT] = NULL;
  } else { 
    /* typical binary search tree insert, descend tree to leaf and insert */
    while (iter_node) {
      if(the_node->value == iter_node->value) return(iter_node);
      RBTree_Direction dir = the_node->value > iter_node->value;
      if (!iter_node->child[dir]) {
        the_node->child[RBT_LEFT] = the_node->child[RBT_RIGHT] = NULL;
        the_node->color = RBT_RED;
        iter_node->child[dir] = the_node;
        the_node->parent = iter_node;
        /* update min/max */
        if (_RBTree_Is_first(the_rbtree, iter_node, dir)) {
          the_rbtree->first[dir] = the_node;
        }
        break;
      } else {
        iter_node = iter_node->child[dir];
      }

    } /* while(iter_node) */
    
    /* verify red-black properties */
    _RBTree_Validate_insert_unprotected(the_node);
  }
  return (RBTree_Node*)0;
}

/** @brief  Validate and fix-up tree properties after deleting a node
 *
 *  This routine is called on a black node, @a the_node, after its deletion.
 *  This function maintains the properties of the red-black tree.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity
 *        of the extract operation.
 */
RTEMS_INLINE_ROUTINE void _RBTree_Extract_validate_unprotected(
    RBTree_Node *the_node
    )
{
  RBTree_Node *parent, *sibling;
  RBTree_Direction dir;

  parent = the_node->parent; 
  if(!parent->parent) return;

  sibling = _RBTree_Sibling(the_node);

  /* continue to correct tree as long as the_node is black and not the root */
  while (!_RBTree_Is_red(the_node) && parent->parent) {

    /* if sibling is red, switch parent (black) and sibling colors, 
     * then rotate parent left, making the sibling be the_node's grandparent.
     * Now the_node has a black sibling and red parent. After rotation, 
     * update sibling pointer.
     */
    if (_RBTree_Is_red(sibling)) {
      parent->color = RBT_RED;
      sibling->color = RBT_BLACK;
      dir = the_node != parent->child[0];
      _RBTree_Rotate(parent, dir);
      sibling = parent->child[!dir];
    }

    /* sibling is black, see if both of its children are also black. */
    if (sibling && 
        !_RBTree_Is_red(sibling->child[RBT_RIGHT]) && 
        !_RBTree_Is_red(sibling->child[RBT_LEFT])) {
        sibling->color = RBT_RED;
        if (_RBTree_Is_red(parent)) {
          parent->color = RBT_BLACK;
          break;
        }
        the_node = parent; /* done if parent is red */
        parent = the_node->parent;
        sibling = _RBTree_Sibling(the_node);
    } else if(sibling) {
      /* at least one of sibling's children is red. we now proceed in two 
       * cases, either the_node is to the left or the right of the parent. 
       * In both cases, first check if one of sibling's children is black, 
       * and if so rotate in the proper direction and update sibling pointer.
       * Then switch the sibling and parent colors, and rotate through parent.
       */
      dir = the_node != parent->child[0];
      if (!_RBTree_Is_red(sibling->child[!dir])) {
        sibling->color = RBT_RED;
        sibling->child[dir]->color = RBT_BLACK;
        _RBTree_Rotate(sibling, !dir);
        sibling = parent->child[!dir];
      }
      sibling->color = parent->color;
      parent->color = RBT_BLACK;
      sibling->child[!dir]->color = RBT_BLACK;
      _RBTree_Rotate(parent, dir);
      break; /* done */
    }
  } /* while */
  if(!the_node->parent->parent) the_node->color = RBT_BLACK;
}

/** @brief Extract a Node (unprotected)
 *
 *  This routine extracts (removes) @a the_node from @a the_rbtree.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity
 *        of the extract operation.
 */
RTEMS_INLINE_ROUTINE void _RBTree_Extract_unprotected(
    RBTree_Control *the_rbtree,
    RBTree_Node *the_node
    )
{
  RBTree_Node *leaf, *target;
  RBTree_Color victim_color;
  RBTree_Direction dir;

  if(!the_node) return;

  /* check if min needs to be updated */
  if (the_node == the_rbtree->first[RBT_LEFT]) {
    if (the_node->child[RBT_RIGHT])
      the_rbtree->first[RBT_LEFT] = the_node->child[RBT_RIGHT];
    else {
      the_rbtree->first[RBT_LEFT] = the_node->parent;
      if(_RBTree_Are_nodes_equal((RBTree_Node *)the_rbtree, 
            the_rbtree->first[RBT_LEFT]))
        the_rbtree->first[RBT_LEFT] = NULL;
    }
  }
  /* check if max needs to be updated: note, min can equal max (1 element) */
  if (the_node == the_rbtree->first[RBT_RIGHT]) {
    if (the_node->child[RBT_LEFT])
      the_rbtree->first[RBT_RIGHT] = the_node->child[RBT_LEFT];
    else {
      the_rbtree->first[RBT_RIGHT] = the_node->parent;
      if(_RBTree_Are_nodes_equal((RBTree_Node *)the_rbtree, 
            the_rbtree->first[RBT_RIGHT]))
        the_rbtree->first[RBT_RIGHT] = NULL;
    }
  }

  /* if the_node has at most one non-null child then it is safe to proceed
   * check if both children are non-null, if so then we must find a target node
   * either max in node->child[RBT_LEFT] or min in node->child[RBT_RIGHT], 
   * and replace the_node with the target node. This maintains the binary 
   * search tree property, but may violate the red-black properties.
   */

  if (the_node->child[RBT_LEFT] && the_node->child[RBT_RIGHT]) {
    target = the_node->child[RBT_LEFT]; /* find max in node->child[RBT_LEFT] */
    while (target->child[RBT_RIGHT]) target = target->child[RBT_RIGHT];

    /* if the target node has a child, need to move it up the tree into 
     * target's position (target is the right child of target->parent) 
     * when target vacates it. if there is no child, then target->parent 
     * should become NULL. This may cause the coloring to be violated.
     * For now we store the color of the node being deleted in victim_color.
     */
     leaf = target->child[RBT_LEFT];
    if(leaf) { 
      leaf->parent = target->parent;
    } else {
      /* fix the tree here if the child is a null leaf. */
      _RBTree_Extract_validate_unprotected(target);
    }
    victim_color = target->color;
    dir = target != target->parent->child[0];
    target->parent->child[dir] = leaf;

    /* now replace the_node with target */
    dir = the_node != the_node->parent->child[0];
    the_node->parent->child[dir] = target;

    /* set target's new children to the original node's children */
    target->child[RBT_RIGHT] = the_node->child[RBT_RIGHT];
    the_node->child[RBT_RIGHT]->parent = target;
    target->child[RBT_LEFT] = the_node->child[RBT_LEFT];
    the_node->child[RBT_LEFT]->parent = target;

    /* finally, update the parent node and recolor. target has completely 
     * replaced the_node, and target's child has moved up the tree if needed.
     * the_node is no longer part of the tree, although it has valid pointers
     * still.
     */
    target->parent = the_node->parent;
    target->color = the_node->color;
  } else { 
    /* the_node has at most 1 non-null child. Move the child in to 
     * the_node's location in the tree. This may cause the coloring to be 
     * violated. We will fix it later.
     * For now we store the color of the node being deleted in victim_color.
     */
    leaf = the_node->child[RBT_LEFT] ? 
              the_node->child[RBT_LEFT] : the_node->child[RBT_RIGHT];
    if( leaf ) {
      leaf->parent = the_node->parent;
    } else {
      /* fix the tree here if the child is a null leaf. */
      _RBTree_Extract_validate_unprotected(the_node);
    }
    victim_color = the_node->color;

    /* remove the_node from the tree */
    dir = the_node != the_node->parent->child[0];
    the_node->parent->child[dir] = leaf;
  }

  /* fix coloring. leaf has moved up the tree. The color of the deleted 
   * node is in victim_color. There are three cases:
   *   1. Deleted a red node, its child must be black. Nothing must be done. 
   *   2. Deleted a black node and the child is red. Paint child black.
   *   3. Deleted a black node and its child is black. This requires some
   *      care and rotations.
   */
  if (victim_color == RBT_BLACK) { /* eliminate case 1 */
    if (_RBTree_Is_red(leaf))
      leaf->color = RBT_BLACK; /* case 2 */
    else if(leaf)
      _RBTree_Extract_validate_unprotected(leaf); /* case 3 */
  }

  /* Wipe the_node */
  _RBTree_Set_off_rbtree(the_node);

  /* set root to black, if it exists */
  if (the_rbtree->root) the_rbtree->root->color = RBT_BLACK;
}

/** @brief Get the First Node (unprotected)
 *
 *  This function removes the minimum or maximum node from the_rbtree and 
 *  returns a pointer to that node.  It does NOT disable interrupts to ensure
 *  the atomicity of the get operation.
 *
 *  @param[in] the_rbtree is the rbtree to attempt to get the min node from.
 *  @param[in] dir specifies whether to get minimum (0) or maximum (1)
 *
 *  @return This method returns the min or max node on the rbtree, or NULL.
 *
 *  @note This routine may return NULL if the RBTree is empty.
 */
RTEMS_INLINE_ROUTINE RBTree_Node *_RBTree_Get_unprotected(
    RBTree_Control *the_rbtree,
    RBTree_Direction dir
    )
{
  RBTree_Node *the_node = the_rbtree->first[dir];
  _RBTree_Extract_unprotected(the_rbtree, the_node);
  return the_node;
}

#endif
/* end of include file */
