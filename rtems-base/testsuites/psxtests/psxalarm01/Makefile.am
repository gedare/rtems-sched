##
## $Id: Makefile.am,v 1.3 2010/06/23 22:49:57 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxalarm01
psxalarm01_SOURCES = init.c ../include/pmacros.h

dist_rtems_tests_DATA = psxalarm01.scn
dist_rtems_tests_DATA += psxalarm01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxalarm01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxalarm01_OBJECTS) $(psxalarm01_LDADD)
LINK_LIBS = $(psxalarm01_LDLIBS)

psxalarm01$(EXEEXT): $(psxalarm01_OBJECTS) $(psxalarm01_DEPENDENCIES)
	@rm -f psxalarm01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
