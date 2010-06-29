/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_link.c,v 1.2 2010/06/29 01:53:18 joel Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int rtems_filesystem_default_link_t(
 rtems_filesystem_location_info_t  *to_loc,      /* IN */
 rtems_filesystem_location_info_t  *parent_loc,  /* IN */
 const char                        *name         /* IN */
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}

