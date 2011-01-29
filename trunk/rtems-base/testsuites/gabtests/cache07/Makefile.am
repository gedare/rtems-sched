##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = cache07
cache07_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = cache07.scn
dist_rtems_tests_DATA += cache07.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

cache07_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(cache07_OBJECTS) $(cache07_LDADD)
LINK_LIBS = $(cache07_LDLIBS)

cache07$(EXEEXT): $(cache07_OBJECTS) $(cache07_DEPENDENCIES)
	@rm -f cache07$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
