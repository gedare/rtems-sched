/*
 *  $Id: setsid.c,v 1.3 2010/08/03 15:56:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>

#include <rtems/seterr.h>

/*PAGE
 *
 *  4.3.2 Create Session and Set Process Group ID, P1003.1b-1993, p. 88
 */

pid_t setsid( void )
{
  rtems_set_errno_and_return_minus_one( EPERM );
}
