##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spinpause
spinpause_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spinpause.scn
dist_rtems_tests_DATA += spinpause.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spinpause_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spinpause_OBJECTS) $(spinpause_LDADD)
LINK_LIBS = $(spinpause_LDLIBS)

spinpause$(EXEEXT): $(spinpause_OBJECTS) $(spinpause_DEPENDENCIES)
	@rm -f spinpause$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
