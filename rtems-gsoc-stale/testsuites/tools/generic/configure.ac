## Process this file with autoconf to produce a configure script.
## 
## $Id: configure.ac,v 1.13 2006/12/02 06:06:15 ralf Exp $

AC_PREREQ(2.60)
AC_INIT([rtems-c-src-tests-tools-generic],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([sorttimes.in])
RTEMS_TOP(../../..)

RTEMS_CANONICAL_TARGET_CPU

AM_INIT_AUTOMAKE([no-define foreign 1.10])
AM_MAINTAINER_MODE

RTEMS_PATH_KSH

RTEMS_TOOLPATHS
AC_SUBST(program_prefix)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile
difftest
sorttimes])
AC_OUTPUT
