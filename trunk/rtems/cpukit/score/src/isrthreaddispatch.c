/**
 * @file
 *
 * @brief Thread dispatch after interrupt processing.
 */

/*
 * Copyright (c) 2009 embedded brains GmbH
 *
 * embedded brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * <rtems@embedded-brains.de>
 *
 * Copyright (c) 2009 Till Straumann <strauman@slac.stanford.edu>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/score/apiext.h>

#if ( CPU_ENABLE_C_ISR_DISPATCH_IMPLEMENTATION == TRUE )

void _ISR_Thread_dispatch( void )
{
  if ( _Thread_Dispatch_necessary ) {
    _Thread_Dispatch();
  }
}

#endif /* CPU_ENABLE_C_ISR_DISPATCH_IMPLEMENTATION */
