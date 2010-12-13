/*
 * edfsupport.c
 *
 * see system.h for license
 */

#include "system.h"

#define MS_PER_S (1000)
#define US_PER_MS (1000)
#define NS_PER_US (1000)

#define US_PER_S (MS_PER_S * US_PER_MS)
#define NS_PER_S (US_PER_MS * NS_PER_US)

void set_timespec_from_us( struct timespec *ts, uint32_t time_us )
{
  uint32_t time_ns = time_us * NS_PER_US;
  uint32_t time_s = time_us / US_PER_S;
  time_ns = time_ns - time_s * NS_PER_S;

  _Timespec_Set( ts, time_s, time_ns );
}

