##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin49
spspin49_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin49.scn
dist_rtems_tests_DATA += spspin49.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin49_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin49_OBJECTS) $(spspin49_LDADD)
LINK_LIBS = $(spspin49_LDLIBS)

spspin49$(EXEEXT): $(spspin49_OBJECTS) $(spspin49_DEPENDENCIES)
	@rm -f spspin49$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
