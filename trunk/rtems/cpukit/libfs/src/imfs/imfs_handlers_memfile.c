/*
 *  Memfile Operations Tables for the IMFS
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_handlers_memfile.c,v 1.13 2010/07/01 20:18:41 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>

#include "imfs.h"

/*
 *  Set of operations handlers for operations on memfile entities.
 */

const rtems_filesystem_file_handlers_r IMFS_memfile_handlers = {
  memfile_open,
  memfile_close,
  memfile_read,
  memfile_write,
  memfile_ioctl,
  memfile_lseek,
  IMFS_stat,
  IMFS_fchmod,
  memfile_ftruncate,
  rtems_filesystem_default_fpathconf,
  IMFS_fdatasync,      /* fsync */
  IMFS_fdatasync,
  IMFS_fcntl,
  IMFS_rmnod
};
