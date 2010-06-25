/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_evalpath.c,v 1.1 2010/06/25 14:23:47 jennifer Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>

int rtems_filesystem_default_evalpath_t(
  const char                        *pathname,      /* IN     */
  size_t                             pathnamelen,   /* IN     */
  int                                flags,         /* IN     */
  rtems_filesystem_location_info_t  *pathloc        /* IN/OUT */
)
{
  pathloc = NULL;
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}

