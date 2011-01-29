##
##  $Id$
##

MANAGERS = io semaphore

rtems_tests_PROGRAMS = dijkstra_small_sort_HWPQ
dijkstra_small_sort_HWPQ_SOURCES = init.c FileSystemImage.c

#dist_rtems_tests_DATA = dijkstra_small_sort_HWPQ.scn
#dist_rtems_tests_DATA += dijkstra_small_sort_HWPQ.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

dijkstra_small_sort_HWPQ_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(dijkstra_small_sort_HWPQ_OBJECTS) $(dijkstra_small_sort_HWPQ_LDADD)
LINK_LIBS = $(dijkstra_small_sort_HWPQ_LDLIBS)

dijkstra_small_sort_HWPQ$(EXEEXT): $(dijkstra_small_sort_HWPQ_OBJECTS) $(dijkstra_small_sort_HWPQ_DEPENDENCIES)
	@rm -f dijkstra_small_sort_HWPQ$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
