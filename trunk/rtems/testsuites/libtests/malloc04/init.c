/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2010/07/14 23:23:12 joel Exp $
 */

#include <tmacros.h>
#include "test_support.h"
#include <rtems/libcsupport.h>
#include <rtems/malloc.h>
#include <errno.h>

char Malloc_Heap[ 128 ] CPU_STRUCTURE_ALIGNMENT;
int sbrk_count;
Heap_Control Heap_Holder;

/* Heap variables we need to peek and poke at */
extern Heap_Control *RTEMS_Malloc_Heap;
extern size_t  RTEMS_Malloc_Sbrk_amount;
extern rtems_malloc_sbrk_functions_t *rtems_malloc_sbrk_helpers;
extern rtems_malloc_sbrk_functions_t  rtems_malloc_sbrk_helpers_table;

size_t offset;

void * sbrk(ptrdiff_t incr)
{
  void *p = (void *) -1;

  printf( "sbrk(%td)\n", incr );
  if ( sbrk_count == -1 ) {
    p = (void *) (NULL - 2);
  } else if ( offset + incr < sizeof(Malloc_Heap) ) {
     p = &Malloc_Heap[ offset ];
     offset += incr;
  } else {
    if ( sbrk_count == 0 )
      p = (void *) rtems_task_create;
    sbrk_count++;
  }

  sbrk_count++;
  return p;
}

rtems_task Init(
  rtems_task_argument argument
)
{
  void *p1, *p2, *p3, *p4;

  sbrk_count = 0;
  offset     = 0;

  puts( "\n\n*** TEST MALLOC 04 ***" );

  /* Safe information on real heap */
  Heap_Holder = *RTEMS_Malloc_Heap;
  rtems_malloc_sbrk_helpers = &rtems_malloc_sbrk_helpers_table;

  puts( "Initialize heap with some memory" );
  offset     = 64;
  sbrk_count = 0;
  RTEMS_Malloc_Initialize( Malloc_Heap, 64, 64 );
  p1 = malloc(64);
  p2 = malloc(64);
  p3 = malloc(48);
  p4 = malloc(48);
  
  puts( "Initialize heap with some memory - return address out of heap" );
  RTEMS_Malloc_Initialize( &Malloc_Heap[1], 64, 64 );
  offset     = 64;
  sbrk_count = -1;
  p1 = malloc( 127 );
  rtems_test_assert( p1 == (void *) NULL );
  rtems_test_assert( errno == ENOMEM );
  

  RTEMS_Malloc_Initialize( Malloc_Heap, 64, 64 );
  puts( "Initialize heap with some unaligned memory" );
  offset     = 65;
  sbrk_count = 0;
  RTEMS_Malloc_Initialize( &Malloc_Heap[1], 64, 64 );
  p1 = malloc(64);
  p2 = malloc(64);
  p3 = malloc(48);

  puts( "Initialize heap with no memory (sbrk aligned)" );
  offset     = 7;
  sbrk_count = 0;
  RTEMS_Malloc_Initialize( NULL, 0, 64 );
  p1 = malloc(64);
  p2 = malloc(64);
  p3 = malloc(48);
  p4 = malloc(48);
  
  puts( "Initialize heap with no memory (sbrk aligned)" );
  offset     = 0;
  sbrk_count = 0;
  RTEMS_Malloc_Initialize( NULL, 0, 64 );
  p1 = malloc(64);
  
  puts( "Set sbrk amount in heap to 0" );
  offset     = 0;
  sbrk_count = 0;
  RTEMS_Malloc_Initialize( NULL, 0, 64 );
  RTEMS_Malloc_Sbrk_amount = 0;
  p4 = malloc(48);

  /* Restore information on real heap */
  *RTEMS_Malloc_Heap = Heap_Holder;
  rtems_malloc_sbrk_helpers = NULL;

  puts( "*** END OF TEST MALLOC 04 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
