/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_freenode.c,v 1.1 2010/06/25 14:23:47 jennifer Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>

int rtems_filesystem_default_freenode_t(
 rtems_filesystem_location_info_t      *pathloc       /* IN */
)
{
  return 0;
}

