# $Id: Makefile.am,v 1.37 2010/12/11 12:56:41 ralf Exp $

rtems_api = 4.11
TARGET = sh-rtems4.11

include $(top_srcdir)/mkspec.am

BINUTILS_VERS = 2.21
BINUTILS_PKGVERS = $(BINUTILS_VERS)
BINUTILS_RPMREL = 1
include ../binutils.am
BINUTILS_OPTS +=

GCC_VERS = 4.5.2
GCC_PKGVERS = $(GCC_VERS)-RC-20101208
GCC_RPMREL = 1
NEWLIB_VERS = 1.18.0
NEWLIB_PKGVERS = $(NEWLIB_VERS)
NEWLIB_RPMREL = `expr $(GCC_RPMREL) + 26`
include ../gcc.am
GCC_OPTS += --languages=cxx

GDB_VERS = 7.2
GDB_PKGVERS = $(GDB_VERS)
GDB_RPMREL = 1
include ../gdb.am
GDB_OPTS +=

CPUKIT_VERS = 4.9.99.0
CPUKIT_PKGVERS = $(CPUKIT_VERS)-20090206-2
CPUKIT_RPMREL = 1
include ../cpukit.am
CPUKIT_OPTS +=
