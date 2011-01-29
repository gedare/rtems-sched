/*
 *  Scheduler Handler
 *
 *  Copyright (C) 2010 Gedare Bloom.
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/percpu.h>
#include <rtems/score/scheduler.h>
#include <rtems/score/scheduleredf.h>
#include <rtems/score/thread.h>

/*
 * _Scheduler_edf_Schedule
 *
 * This kernel routine implements scheduling decision logic for edf-based
 * scheduling.  
 *
 * Input parameters:
 *   the_scheduler  - pointer to scheduler control
 *
 * Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 */

void _Scheduler_edf_Schedule(
  Scheduler_Control     *the_scheduler
)
{
  _Scheduler_edf_Schedule_body( the_scheduler );
}
