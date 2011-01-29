##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin00
spspin00_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin00.scn
dist_rtems_tests_DATA += spspin00.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin00_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin00_OBJECTS) $(spspin00_LDADD)
LINK_LIBS = $(spspin00_LDLIBS)

spspin00$(EXEEXT): $(spspin00_OBJECTS) $(spspin00_DEPENDENCIES)
	@rm -f spspin00$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
