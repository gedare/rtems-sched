/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_ioctl.c,v 1.1 2010/06/25 14:23:47 jennifer Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>

int rtems_filesystem_default_ioctl(
  rtems_libio_t *iop,
  uint32_t       command,
  void          *buffer
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}
