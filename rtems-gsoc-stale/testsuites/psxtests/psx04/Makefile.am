##
## $Id: Makefile.am,v 1.27 2010/06/23 22:49:57 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psx04
psx04_SOURCES = init.c task1.c task2.c task3.c system.h ../include/pmacros.h

dist_rtems_tests_DATA = psx04.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psx04_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psx04_OBJECTS) $(psx04_LDADD)
LINK_LIBS = $(psx04_LDLIBS)

psx04$(EXEEXT): $(psx04_OBJECTS) $(psx04_DEPENDENCIES)
	@rm -f psx04$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
