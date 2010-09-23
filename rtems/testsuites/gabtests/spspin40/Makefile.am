##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin40
spspin40_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin40.scn
dist_rtems_tests_DATA += spspin40.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin40_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin40_OBJECTS) $(spspin40_LDADD)
LINK_LIBS = $(spspin40_LDLIBS)

spspin40$(EXEEXT): $(spspin40_OBJECTS) $(spspin40_DEPENDENCIES)
	@rm -f spspin40$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
