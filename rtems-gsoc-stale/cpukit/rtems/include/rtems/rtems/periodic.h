/**
 * @file rtems/rtems/periodic.h
 *
 *  This include file contains all the public constants, structures, and
 *  prototypes associated with the Periodic Manager.  This manager
 *  provides facilities to implement threads which execute in a periodic
 *  fashion.
 *
 *  Directives provided are:
 *
 *     - create a periodic timer
 *     - cancel a period
 *     - delete a periodic timer
 *     - conclude current and start the next period
 *     - obtain status information on a period
 */

/*  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Copyright (c) 2010 Gedare Bloom
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_RTEMS_PERIODIC_H
#define _RTEMS_RTEMS_PERIODIC_H

/**
 *  @defgroup ClassicPeriodic Periodic Manager
 *
 *  @ingroup ClassicRTEMS
 *
 *  This encapsulates functionality related to the
 *  Classic API Periodic Manager.
 *
 *  Statistics are kept for each period and can be obtained or printed via
 *  API calls.  The statistics kept include minimum, maximum and average times
 *  for both cpu usage and wall time.  The statistics indicate the execution time
 *  used by the owning thread between successive calls to rtems_periodic_period.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  This is the public type used for the periodic timing
 *  statistics.
 */
#ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
  #include <rtems/score/timespec.h>

  typedef struct timespec rtems_periodic_period_time_t;
#else
  typedef uint32_t rtems_periodic_period_time_t;
#endif

#include <rtems/score/periodic.h>

#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>

#include <string.h>

typedef Periodic_Period_states rtems_periodic_period_states;

/**
 *  The following defines the PUBLIC data structure that has the
 *  statistics kept on each period instance.
 *
 *  @note The public structure uses struct timespec while the
 *        internal one uses Timestamp_Control.
 */
typedef struct {
  /** This field contains the number of periods executed. */
  uint32_t     count;
  /** This field contains the number of periods missed. */
  uint32_t     missed_count;

  /** This field contains the least amount of CPU time used in a period. */
  rtems_thread_cpu_usage_t             min_cpu_time;
  /** This field contains the highest amount of CPU time used in a period. */
  rtems_thread_cpu_usage_t             max_cpu_time;
  /** This field contains the total amount of wall time used in a period. */
  rtems_thread_cpu_usage_t             total_cpu_time;

  /** This field contains the least amount of wall time used in a period. */
  rtems_periodic_period_time_t         min_wall_time;
  /** This field contains the highest amount of wall time used in a period. */
  rtems_periodic_period_time_t         max_wall_time;
  /** This field contains the total amount of CPU time used in a period. */
  rtems_periodic_period_time_t         total_wall_time;
}  rtems_periodic_period_statistics;

/**
 *  The following defines the period status structure.
 */
typedef struct {
  /** This is the Id of the thread using this period. */
  rtems_id                             owner;

  /** This is the current state of this period. */
  rtems_periodic_period_states         state;

  /**
   *  This is the length of wall time that has passed since this period
   *  was last initiated.  If the period is expired or has not been initiated,
   *  then this field has no meaning.
   */
  rtems_periodic_period_time_t         since_last_period;

  /**
   *  This is the amount of CPU time that has been used since this period
   *  was last initiated.  If the period is expired or has not been initiated,
   *  then this field has no meaning.
   */
  rtems_thread_cpu_usage_t             executed_since_last_period;
}  rtems_periodic_period_status;


/**
 *  @brief rtems_periodic_create
 *
 *  This routine implements the periodic_create directive.  The
 *  period will have the name name.  It returns the id of the
 *  created period in ID.
 */
rtems_status_code rtems_periodic_create(
  rtems_name    name,
  rtems_id     *id
);

/**
 *  @brief rtems_periodic_ident
 *
 *  This routine implements the rtems_periodic_ident directive.
 *  It returns the period ID associated with name.  If more than one period
 *  is named name, then the period to which the ID belongs is arbitrary.
 */
rtems_status_code rtems_periodic_ident(
  rtems_name    name,
  rtems_id     *id
);

/**
 *  @brief rtems_periodic_cancel
 *
 *  This routine implements the rtems_periodic_cancel directive.  This
 *  directive stops the period associated with ID from continuing to
 *  run.
 */
rtems_status_code rtems_periodic_cancel(
  rtems_id   id
);

/**
 *  @brief rtems_periodic_delete
 *
 *  This routine implements the rtems_periodic_delete directive.  The
 *  period indicated by ID is deleted.
 */
rtems_status_code rtems_periodic_delete(
  rtems_id   id
);

/**
 *  @brief rtems_periodic_get_status
 *
 *  This routine implements the rtems_periodic_get_status directive.
 *  Information about the period indicated by ID is returned.
 *
 */
rtems_status_code rtems_periodic_get_status(
  rtems_id                             id,
  rtems_periodic_period_status  *status
);

/**
 *  @brief rtems_periodic_get_statistics
 *
 *  This routine implements the rtems_periodic_get_statistics directive.
 *  Statistics gathered from the use of this period are returned.
 */
rtems_status_code rtems_periodic_get_statistics(
  rtems_id                                id,
  rtems_periodic_period_statistics *statistics
);

/**
 *  @brief rtems_periodic_reset_statistics
 *
 *  This routine allows a thread to reset the statistics information
 *  on a specific period instance.
 */
rtems_status_code rtems_periodic_reset_statistics(
  rtems_id                                 id
);

/**
 *  @brief rtems_periodic_reset_all_statistics
 *
 *  This routine allows a thread to reset the statistics information
 *  on ALL period instances.
 */
void rtems_periodic_reset_all_statistics( void );

/**
 *  @brief rtems_periodic_report_statistics
 *
 *  This routine allows a thread to print the statistics information
 *  on ALL period instances which have non-zero counts using printk.
 */
void rtems_periodic_report_statistics_with_plugin(
  void                  *context,
  rtems_printk_plugin_t  print
);

/**
 *  @brief rtems_periodic_report_statistics
 *
 *  This routine allows a thread to print the statistics information
 *  on ALL period instances which have non-zero counts using printk.
 */
void rtems_periodic_report_statistics( void );

/**
 *  @brief rtems_periodic_period
 *
 *  This routine implements the rtems_periodic_period directive.  When
 *  length is non-zero, this directive initiates the period associated with
 *  ID from continuing for a period of length.  If length is zero, then
 *  result is set to indicate the current state of the period.
 */
rtems_status_code rtems_periodic_period(
  rtems_id        id,
  rtems_interval  length
);

/**@}*/

#endif
/* end of include file */
