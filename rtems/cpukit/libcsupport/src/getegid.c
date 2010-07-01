/*
 *  $Id: getegid.c,v 1.4 2010/07/01 15:37:48 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <limits.h>
#include <string.h>
#include <sys/types.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/seterr.h>
#include <rtems/userenv.h>

/*
 *  4.2.1 Get Real User, Effective User, Ral Group, and Effective Group IDs,
 *        P1003.1b-1993, p. 84
 */

gid_t getegid( void )
{
  return _POSIX_types_Egid;
}
