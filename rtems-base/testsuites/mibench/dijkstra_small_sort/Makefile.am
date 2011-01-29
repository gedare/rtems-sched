##
##  $Id$
##

MANAGERS = io semaphore

rtems_tests_PROGRAMS = dijkstra_small_sort
dijkstra_small_sort_SOURCES = init.c FileSystemImage.c

#dist_rtems_tests_DATA = dijkstra_small_sort.scn
#dist_rtems_tests_DATA += dijkstra_small_sort.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

dijkstra_small_sort_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(dijkstra_small_sort_OBJECTS) $(dijkstra_small_sort_LDADD)
LINK_LIBS = $(dijkstra_small_sort_LDLIBS)

dijkstra_small_sort$(EXEEXT): $(dijkstra_small_sort_OBJECTS) $(dijkstra_small_sort_DEPENDENCIES)
	@rm -f dijkstra_small_sort$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
