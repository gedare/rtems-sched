##
##  $Id: Makefile.am,v 1.16 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = astar00
astar00_SOURCES = init.cc system.h astar00.cpp fsa.h stlastar.h

dist_rtems_tests_DATA = astar00.scn
dist_rtems_tests_DATA += astar00.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

astar00_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(astar00_OBJECTS) $(astar00_LDADD)
LINK_LIBS = $(astar00_LDLIBS)

astar00$(EXEEXT): $(astar00_OBJECTS) $(astar00_DEPENDENCIES)
	@rm -f astar00$(EXEEXT)
	$(make-cxx-exe)

include $(top_srcdir)/../automake/local.am
