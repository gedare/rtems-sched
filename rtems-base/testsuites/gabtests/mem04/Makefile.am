##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = mem04
mem04_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = mem04.scn
dist_rtems_tests_DATA += mem04.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

mem04_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(mem04_OBJECTS) $(mem04_LDADD)
LINK_LIBS = $(mem04_LDLIBS)

mem04$(EXEEXT): $(mem04_OBJECTS) $(mem04_DEPENDENCIES)
	@rm -f mem04$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
