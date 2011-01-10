/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: consume_sems.c,v 1.1 2010/06/22 01:28:13 joel Exp $
 */

#include <rtems.h>

#define MAXIMUM 20
rtems_id Semaphores[MAXIMUM];

rtems_device_driver consume_semaphores_initialize(
  rtems_device_major_number major __attribute__((unused)),
  rtems_device_minor_number minor __attribute__((unused)),
  void *pargp __attribute__((unused))
)
{
  int               sems;
  rtems_status_code status;

  for ( sems=0 ; sems<MAXIMUM ; sems++ ) {
    status = rtems_semaphore_create(
      rtems_build_name( 'S', 'M', '1', ' ' ),
      1,
      RTEMS_DEFAULT_MODES,
      RTEMS_NO_PRIORITY,
      &Semaphores[sems]
    );
    if ( status == RTEMS_TOO_MANY )
     break;
  }

  #if 0
    printk( "Consumed %d\n", sems );
    printk( "Freeing %d\n", SEMAPHORES_REMAINING );
  #endif

  #if defined(SEMAPHORES_REMAINING)
  {
    int i;

    for ( i=0 ; i<SEMAPHORES_REMAINING ; i++ ) {
      (void) rtems_semaphore_delete( Semaphores[i] );
    }
  }
  #endif
  return RTEMS_SUCCESSFUL;
}
