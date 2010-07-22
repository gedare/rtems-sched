/**
 * @file rtems/rtems/ratemon.h
 *
 *  This include file contains all the constants, structures, and
 *  prototypes associated with the Rate Monotonic Manager.  This manager
 *  provides facilities to implement threads which execute in a periodic
 *  fashion.
 *
 *  Directives provided are:
 *
 *     - create a rate monotonic timer
 *     - cancel a period
 *     - delete a rate monotonic timer
 *     - conclude current and start the next period
 *     - obtain status information on a period
 */

/*  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemon.h,v 1.42 2009/12/15 18:26:41 humph Exp $
 */

#ifndef _RTEMS_RTEMS_RATEMON_H
#define _RTEMS_RTEMS_RATEMON_H

#include <rtems/bspIo.h>

/**
 *  @defgroup ClassicRateMon Rate Monotonic Scheduler
 *
 *  @ingroup ClassicRTEMS
 *
 *  This encapsulates functionality related to the
 *  Classic API Rate Monotonic Manager.
 *
 *  Statistics are kept for each period and can be obtained or printed via
 *  API calls.  The statistics kept include minimum, maximum and average times
 *  for both cpu usage and wall time.  The statistics indicate the execution time
 *  used by the owning thread between successive calls to rtems_rate_monotonic_period.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/rtems/periodic.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>

#include <rtems/score/periodic.h>

#include <string.h>

typedef rtems_periodic_period_states rtems_rate_monotonic_period_states; 

typedef rtems_periodic_period_statistics rtems_rate_monotonic_period_statistics;

typedef rtems_periodic_period_status rtems_rate_monotonic_period_status; 

typedef Periodic_Control Rate_monotonic_Control;

/**
 *  @brief rtems_rate_monotonic_create
 *
 *  This routine implements the rate_monotonic_create directive.  The
 *  period will have the name name.  It returns the id of the
 *  created period in ID.
 */
rtems_status_code rtems_rate_monotonic_create(
  rtems_name    name,
  rtems_id     *id
);

/**
 *  @brief rtems_rate_monotonic_ident
 *
 *  This routine implements the rtems_rate_monotonic_ident directive.
 *  It returns the period ID associated with name.  If more than one period
 *  is named name, then the period to which the ID belongs is arbitrary.
 */
rtems_status_code rtems_rate_monotonic_ident(
  rtems_name    name,
  rtems_id     *id
);

/**
 *  @brief rtems_rate_monotonic_cancel
 *
 *  This routine implements the rtems_rate_monotonic_cancel directive.  This
 *  directive stops the period associated with ID from continuing to
 *  run.
 */
rtems_status_code rtems_rate_monotonic_cancel(
  rtems_id   id
);

/**
 *  @brief rtems_rate_monotonic_delete
 *
 *  This routine implements the rtems_rate_monotonic_delete directive.  The
 *  period indicated by ID is deleted.
 */
rtems_status_code rtems_rate_monotonic_delete(
  rtems_id   id
);

/**
 *  @brief rtems_rate_monotonic_get_status
 *
 *  This routine implements the rtems_rate_monotonic_get_status directive.
 *  Information about the period indicated by ID is returned.
 *
 */
rtems_status_code rtems_rate_monotonic_get_status(
  rtems_id                             id,
  rtems_rate_monotonic_period_status  *status
);

/**
 *  @brief rtems_rate_monotonic_get_statistics
 *
 *  This routine implements the rtems_rate_monotonic_get_statistics directive.
 *  Statistics gathered from the use of this period are returned.
 */
rtems_status_code rtems_rate_monotonic_get_statistics(
  rtems_id                                id,
  rtems_rate_monotonic_period_statistics *statistics
);

/**
 *  @brief rtems_rate_monotonic_reset_statistics
 *
 *  This routine allows a thread to reset the statistics information
 *  on a specific period instance.
 */
rtems_status_code rtems_rate_monotonic_reset_statistics(
  rtems_id                                 id
);

/**
 *  @brief rtems_rate_monotonic_reset_all_statistics
 *
 *  This routine allows a thread to reset the statistics information
 *  on ALL period instances.
 */
void rtems_rate_monotonic_reset_all_statistics( void );

/**
 *  @brief rtems_rate_monotonic_report_statistics
 *
 *  This routine allows a thread to print the statistics information
 *  on ALL period instances which have non-zero counts using printk.
 */
void rtems_rate_monotonic_report_statistics_with_plugin(
  void                  *context,
  rtems_printk_plugin_t  print
);

/**
 *  @brief rtems_rate_monotonic_report_statistics
 *
 *  This routine allows a thread to print the statistics information
 *  on ALL period instances which have non-zero counts using printk.
 */
void rtems_rate_monotonic_report_statistics( void );

/**
 *  @brief rtems_rate_monotonic_period
 *
 *  This routine implements the rtems_rate_monotonic_period directive.  When
 *  length is non-zero, this directive initiates the period associated with
 *  ID from continuing for a period of length.  If length is zero, then
 *  result is set to indicate the current state of the period.
 */
rtems_status_code rtems_rate_monotonic_period(
  rtems_id        id,
  rtems_interval  length
);

/**
 *  @brief Rate Monotonic Manager Initialization
 *
 *  This routine performs the initialization necessary for this manager.
 */
void _Rate_monotonic_Manager_initialization(void);


#ifndef __RTEMS_APPLICATION__
#include <rtems/rtems/ratemon.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
