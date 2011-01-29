##
##  $Id$
##

MANAGERS = all

rtems_tests_PROGRAMS = dijkstra01
dijkstra01_SOURCES = init.c FileSystemImage.c dijkstra.c tasks_periodic.c params.h macros.h system.h

#dist_rtems_tests_DATA = dijkstra01.scn
#dist_rtems_tests_DATA += dijkstra01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

dijkstra01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(dijkstra01_OBJECTS) $(dijkstra01_LDADD)
LINK_LIBS = $(dijkstra01_LDLIBS)

dijkstra01$(EXEEXT): $(dijkstra01_OBJECTS) $(dijkstra01_DEPENDENCIES)
	@rm -f dijkstra01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
