##
##  $Id: Makefile.am,v 1.16 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = astarbase
astarbase_SOURCES = init.cc system.h astarbase.cpp fsa.h stlastar.h

dist_rtems_tests_DATA = astarbase.scn
dist_rtems_tests_DATA += astarbase.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

astarbase_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(astarbase_OBJECTS) $(astarbase_LDADD)
LINK_LIBS = $(astarbase_LDLIBS)

astarbase$(EXEEXT): $(astarbase_OBJECTS) $(astarbase_DEPENDENCIES)
	@rm -f astarbase$(EXEEXT)
	$(make-cxx-exe)

include $(top_srcdir)/../automake/local.am
