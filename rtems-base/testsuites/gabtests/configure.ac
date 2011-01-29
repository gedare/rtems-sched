## Process this file with autoconf to produce a configure script.
## 
## $Id: configure.ac,v 1.30 2010/08/16 14:20:48 ralf Exp $

AC_PREREQ(2.67)
AC_INIT([rtems-c-src-tests-samples],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([spspin00])
RTEMS_TOP([../..],[..])

RTEMS_CANONICAL_TARGET_CPU

AM_INIT_AUTOMAKE([no-define foreign 1.11.1])
AM_MAINTAINER_MODE

RTEMS_ENABLE_CXX

RTEMS_ENV_RTEMSBSP

RTEMS_PROJECT_ROOT

RTEMS_PROG_CC_FOR_TARGET

RTEMS_PROG_CXX_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS

RTEMS_CHECK_CUSTOM_BSP(RTEMS_BSP)
RTEMS_CHECK_CPUOPTS([RTEMS_MULTIPROCESSING])
RTEMS_CHECK_CXX(RTEMS_BSP)
RTEMS_CHECK_CPUOPTS([RTEMS_NETWORKING])


CXXTESTS=$HAS_CPLUSPLUS
AS_IF([test $HAS_CPLUSPLUS = yes],[
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([cstdio cstdlib iostream],[],[CXXTESTS=no])
  AC_CACHE_CHECK(
  [if iostream supports std:: namespace],
  [rtems_cv_HAVE_IOSTREAM_STD_NAMESPACE],
  [AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
      [[#include <iostream>]], 
      [[std::cout << "hello" << std::endl;]])
    ],
    [rtems_cv_HAVE_IOSTREAM_STD_NAMESPACE=yes],
    [rtems_cv_HAVE_IOSTREAM_STD_NAMESPACE=no])
  ])
  AS_IF([test $rtems_cv_HAVE_IOSTREAM_STD_NAMESPACE = no],[CXXTESTS=no])
  AS_IF([test $CXXTESTS = no],[
    AC_MSG_WARN([disabling C++ tests])
  ])
  AC_LANG_POP
])

AM_CONDITIONAL([CXXTESTS],[test $CXXTESTS = "yes"])
AM_CONDITIONAL(NETTESTS,test "$rtems_cv_RTEMS_NETWORKING" = "yes")
AM_CONDITIONAL(MPTESTS,test "$rtems_cv_RTEMS_MULTIPROCESSING" = "yes")

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile
astar00/Makefile
astar01/Makefile
astar02/Makefile
cache00/Makefile
cache01/Makefile
cache02/Makefile
cache03/Makefile
cache04/Makefile
cache05/Makefile
cache06/Makefile
cache07/Makefile
cache08/Makefile
cache09/Makefile
dijkstra00/Makefile
dijkstra01/Makefile
mem00/Makefile
mem01/Makefile
mem02/Makefile
mem03/Makefile
mem04/Makefile
mem05/Makefile
mem06/Makefile
mem07/Makefile
mem08/Makefile
mem09/Makefile
spspin09/Makefile
spspin08/Makefile
spspin07/Makefile
spspin06/Makefile
spspin05/Makefile
spspin04/Makefile
spspin03/Makefile
spspin02/Makefile
spspin01/Makefile
spspin00/Makefile
])
AC_OUTPUT
