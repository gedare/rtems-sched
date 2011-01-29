##
##  $Id: Makefile.am,v 1.16 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = astar02
astar02_SOURCES = init.cc system.h astar02.cpp fsa.h stlastar.h

dist_rtems_tests_DATA = astar02.scn
dist_rtems_tests_DATA += astar02.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

astar02_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(astar02_OBJECTS) $(astar02_LDADD)
LINK_LIBS = $(astar02_LDLIBS)

astar02$(EXEEXT): $(astar02_OBJECTS) $(astar02_DEPENDENCIES)
	@rm -f astar02$(EXEEXT)
	$(make-cxx-exe)

include $(top_srcdir)/../automake/local.am
