## Process this file with autoconf to produce a configure script.
##
## $Id: configure.ac,v 1.10 2009/11/28 06:28:40 ralf Exp $

AC_PREREQ(2.60)
AC_INIT([rtems-c-src-lib-libbsp-m68k-genmcf548x],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.10])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

RTEMS_CHECK_NETWORKING

AM_CONDITIONAL(HAS_NETWORKING,test "$HAS_NETWORKING" = "yes")

RTEMS_BSPOPTS_SET([BSP_CPU_CLOCK_SPEED],[COBRA5475],[132000000])
RTEMS_BSPOPTS_SET([BSP_CPU_CLOCK_SPEED],[m5484FireEngine],[100000000])
RTEMS_BSPOPTS_SET([BSP_CPU_CLOCK_SPEED],[*],[100000000])
RTEMS_BSPOPTS_HELP([BSP_CPU_CLOCK_SPEED],
[The bus clock to be used inside the mcf54xx])

RTEMS_BSPOPTS_SET([M5484FIREENGINE],[m5484FireEngine],[1])
RTEMS_BSPOPTS_HELP([M5484FIREENGINE],
[If defined, use custom settings for the m5484FireEngine BSP.])

RTEMS_BSPOPTS_SET([BSP_CONSOLE_BAUD],[COBRA5475],[19200])
RTEMS_BSPOPTS_SET([BSP_CONSOLE_BAUD],[*],[9600])
RTEMS_BSPOPTS_HELP([BSP_CONSOLE_BAUD],[initial baudrate for UARTs])

RTEMS_BSPOPTS_SET([HAS_DBUG],[COBRA5475],[1])
RTEMS_BSPOPTS_SET([HAS_DBUG],[*],[0])
RTEMS_BSPOPTS_HELP([HAS_DBUG],
[If defined, we will not boot from RESET, but from Freescale DBug monitor.])

RTEMS_BSPOPTS_SET([HAS_LOW_LEVEL_INIT],[m5484FireEngine],[1])
RTEMS_BSPOPTS_SET([HAS_LOW_LEVEL_INIT],[*],[0])
RTEMS_BSPOPTS_HELP([HAS_DBUG],
[If defined, we will do all the low level init of the chip (like bus/memory...).])

RTEMS_BSP_CLEANUP_OPTIONS(0, 1)
RTEMS_BSP_LINKCMDS

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
