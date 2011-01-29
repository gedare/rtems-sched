##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = mem07
mem07_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = mem07.scn
dist_rtems_tests_DATA += mem07.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

mem07_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(mem07_OBJECTS) $(mem07_LDADD)
LINK_LIBS = $(mem07_LDLIBS)

mem07$(EXEEXT): $(mem07_OBJECTS) $(mem07_DEPENDENCIES)
	@rm -f mem07$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
