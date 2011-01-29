##
##  $Id: Makefile.am,v 1.16 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = astar01
astar01_SOURCES = init.cc system.h astar01.cpp fsa.h stlastar.h

dist_rtems_tests_DATA = astar01.scn
dist_rtems_tests_DATA += astar01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

astar01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(astar01_OBJECTS) $(astar01_LDADD)
LINK_LIBS = $(astar01_LDLIBS)

astar01$(EXEEXT): $(astar01_OBJECTS) $(astar01_DEPENDENCIES)
	@rm -f astar01$(EXEEXT)
	$(make-cxx-exe)

include $(top_srcdir)/../automake/local.am
