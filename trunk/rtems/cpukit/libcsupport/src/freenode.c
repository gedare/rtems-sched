/*
 *  freenode()
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: freenode.c,v 1.1 2010/06/22 20:03:41 jennifer Exp $
 */

#include <stdlib.h>
#include <rtems/libio_.h>

void rtems_filesystem_freenode( rtems_filesystem_location_info_t *_node )
{
  if ( _node->ops )
    if ( _node->ops->freenod_h )
      _node->ops->freenod_h(_node );
}
