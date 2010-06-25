/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_mount.c,v 1.1 2010/06/25 14:23:48 jennifer Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>

int rtems_filesystem_default_mount_t (
   rtems_filesystem_mount_table_entry_t *mt_entry     /* IN */
)
{
  return 0;
}
