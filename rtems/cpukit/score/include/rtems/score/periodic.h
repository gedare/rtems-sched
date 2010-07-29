/**
 *  @file  rtems/score/periodic.h
 *
 *  This include file contains all the constants and structures associated
 *  with the Periodic Manager.
 */

/*
 *  Copyright (c) 2010 Gedare Bloom.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_PERIODIC_H
#define _RTEMS_SCORE_PERIODIC_H

/**
 *  @defgroup ScorePeriodic Periodic Handler
 *
 *  This handler encapsulates functionality related to managing sets of threads
 *  that are periodic tasks.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  This is the internal type used for the periodic timing
 *  statistics.
 */
#ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
  #include <rtems/score/timestamp.h>

  typedef Timestamp_Control Periodic_Period_time_t;
#else
  typedef uint32_t Periodic_Period_time_t;
#endif

#include <rtems/score/object.h>
#include <rtems/score/thread.h>
#include <rtems/score/watchdog.h>

/**
 *  The following enumerated type defines the states in which a
 *  period may be.
 */
typedef enum {
  /**
   * This value indicates the period is off the watchdog chain,
   * and has never been initialized.
   */
  PERIODIC_INACTIVE,

  /**
   * This value indicates the period is on the watchdog chain, and
   * the owner is blocked waiting on it.
   */
  PERIODIC_OWNER_IS_BLOCKING,

  /**
   * This value indicates the period is on the watchdog chain, and
   * running.  The owner should be executed or blocked waiting on
   * another object.
   */
  PERIODIC_ACTIVE,

  /**
   * This value indicates the period is on the watchdog chain, and
   * has expired.  The owner should be blocked waiting for the next period.
   */
  PERIODIC_EXPIRED_WHILE_BLOCKING,

  /**
   * This value indicates the period is off the watchdog chain, and
   * has expired.  The owner is still executing and has taken too much
   * all time to complete this iteration of the period.
   */
  PERIODIC_EXPIRED
}   Periodic_Period_states;

/**
 *  The following constant is the interval passed to the rate_monontonic_period
 *  directive to obtain status information.
 */
#define RTEMS_PERIOD_STATUS       WATCHDOG_NO_TIMEOUT

/**
 *  The following defines the INTERNAL data structure that has the
 *  statistics kept on each period instance.
 */
typedef struct {
  /** This field contains the number of periods executed. */
  uint32_t     count;
  /** This field contains the number of periods missed. */
  uint32_t     missed_count;

  /** This field contains the least amount of CPU time used in a period. */
  Thread_CPU_usage_t                   min_cpu_time;
  /** This field contains the highest amount of CPU time used in a period. */
  Thread_CPU_usage_t                   max_cpu_time;
  /** This field contains the total amount of wall time used in a period. */
  Thread_CPU_usage_t                   total_cpu_time;

  /** This field contains the least amount of wall time used in a period. */
  Periodic_Period_time_t         min_wall_time;
  /** This field contains the highest amount of wall time used in a period. */
  Periodic_Period_time_t         max_wall_time;
  /** This field contains the total amount of CPU time used in a period. */
  Periodic_Period_time_t         total_wall_time;
}  Periodic_Statistics;


/**
 *  The following structure defines the control block used to manage
 *  each period.
 */
typedef struct {
  /** This field is the object management portion of a Period instance. */
  Objects_Control                         Object;

  /** This is the timer used to provide the unblocking mechanism. */
  Watchdog_Control                        Timer;

  /** This field indicates the current state of the period. */
  Periodic_Period_states                  state;

  /**
   * This field contains the length of the next period to be
   * executed.
   */
  uint32_t                                next_length;

  /**
   * This field contains a pointer to the TCB for the thread
   * which owns and uses this period instance.
   */
  Thread_Control                         *owner;

  /**
   * This field contains the cpu usage value of the owning thread when
   * the period was initiated.  It is used to compute the period's
   * statistics.
   */
  Thread_CPU_usage_t                      cpu_usage_period_initiated;

  /**
   * This field contains the wall time value when the period
   * was initiated.  It is used to compute the period's statistics.
   */
  Periodic_Period_time_t                  time_period_initiated;

  /**
   * This field contains the statistics maintained for the period.
   */
  Periodic_Statistics                     Statistics;
}   Periodic_Control;

/**
 *  @brief Periodic Period Class Management Structure
 *
 *  This instance of Objects_Information is used to manage the
 *  set of periodic period instances.
 */
SCORE_EXTERN Objects_Information _Periodic_Information;

/**
 *  @brief Periodic Manager Initialization
 *
 *  This routine performs the initialization necessary for this manager.
 */
void _Periodic_Manager_initialization(void);

/**
 *  @brief _Periodic_Timeout
 *
 *  This routine is invoked when the period represented
 *  by ID expires.  If the thread which owns this period is blocked
 *  waiting for the period to expire, then it is readied and the
 *  period is restarted.  If the owning thread is not waiting for the
 *  period to expire, then the period is placed in the EXPIRED
 *  state and not restarted.
 */
void _Periodic_Timeout(
  Objects_Id id,
  void       *ignored
);

/**
 *  @brief _Periodic_Get_status(
 *
 *  This routine is invoked to compute the elapsed wall time and cpu
 *  time for a period.
 *
 *  @param[in] the_period points to the period being operated upon.
 *  @param[out] wall_since_last_period is set to the wall time elapsed
 *              since the period was initiated.
 *  @param[out] cpu_since_last_period is set to the cpu time used by the
 *              owning thread since the period was initiated.
 *
 *  @return This routine returns true if the status can be determined
 *          and false otherwise.
 */
bool _Periodic_Get_status(
  Periodic_Control        *the_period,
  Periodic_Period_time_t  *wall_since_last_period,
  Thread_CPU_usage_t            *cpu_since_last_period
);

/**
 *  @brief _Periodic_Initiate_statistics(
 *
 *  This routine is invoked when a period is initiated via an explicit
 *  call to rtems_periodic_period for the period's first iteration
 *  or from _Periodic_Timeout for period iterations 2-n.
 *
 *  @param[in] the_period points to the period being operated upon.
 */
void _Periodic_Initiate_statistics(
  Periodic_Control *the_period
);

/**
 *  @brief _Periodic_Update_statistics
 *
 *  This routine is invoked when a period concludes.
 */
void _Periodic_Update_statistics(
  Periodic_Control    *the_period
);

/**
 *  @brief _Periodic_Reset_wall_time_statistics
 *
 *  This method resets the statistics information for a period instance.
 */
#ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
  #define _Periodic_Reset_wall_time_statistics( _the_period ) \
     do { \
        /* set the minimums to a large value */ \
        _Timestamp_Set( \
          &(_the_period)->Statistics.min_wall_time, \
          0x7fffffff, \
          0x7fffffff \
        ); \
     } while (0)
#else
  #define _Periodic_Reset_wall_time_statistics( _the_period ) \
     do { \
        /* set the minimum to a large value */ \
        (_the_period)->Statistics.min_wall_time = 0xffffffff; \
     } while (0)
#endif

/**
 *  @brief Periodic_Reset_cpu_use_statistics
 *
 *  This helper method resets the period CPU usage statistics structure.
 */
#ifndef __RTEMS_USE_TICKS_FOR_STATISTICS__
  #define _Periodic_Reset_cpu_use_statistics( _the_period ) \
     do { \
        /* set the minimums to a large value */ \
        _Timestamp_Set( \
          &(_the_period)->Statistics.min_cpu_time, \
          0x7fffffff, \
          0x7fffffff \
        ); \
     } while (0)
#else
  #define _Periodic_Reset_cpu_use_statistics( _the_period ) \
     do { \
        /* set the minimum to a large value */ \
        (_the_period)->Statistics.min_cpu_time = 0xffffffff; \
     } while (0)
#endif

/**
 *  @brief Periodic_Reset_statistics
 *
 *  This helper method resets the period wall time statistics structure.
 */
#define _Periodic_Reset_statistics( _the_period ) \
  do { \
    memset( \
      &(_the_period)->Statistics, \
      0, \
      sizeof( rtems_periodic_period_statistics ) \
    ); \
    _Periodic_Reset_cpu_use_statistics( _the_period ); \
    _Periodic_Reset_wall_time_statistics( _the_period ); \
  } while (0)



#ifndef __RTEMS_APPLICATION__

#include <rtems/score/periodic.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
