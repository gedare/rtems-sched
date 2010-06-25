/*
 *  Thread Handler
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: threadsetpriority.c,v 1.4 2005/01/27 05:57:05 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/apiext.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/readyq.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/states.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>

/*PAGE
 *
 * _Thread_Set_priority
 *
 * This directive enables and disables several modes of
 * execution for the requesting thread.
 *
 *  Input parameters:
 *    the_thread   - pointer to thread priority
 *    new_priority - new priority
 *
 *  Output: NONE
 */

void _Thread_Set_priority(
  Thread_Control   *the_thread,
  Priority_Control  new_priority
)
{
  _Priority_Set(&the_thread->current_priority, &new_priority);

  _Ready_queue_Set_ready(&_Thread_Ready_queue, the_thread);

  _Priority_Initialize_information( &the_thread->Priority_map, new_priority );
}
