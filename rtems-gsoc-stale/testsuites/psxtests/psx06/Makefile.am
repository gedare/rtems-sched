##
## $Id: Makefile.am,v 1.27 2010/06/23 22:49:57 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psx06
psx06_SOURCES = init.c task.c task2.c system.h ../include/pmacros.h

dist_rtems_tests_DATA = psx06.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psx06_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psx06_OBJECTS) $(psx06_LDADD)
LINK_LIBS = $(psx06_LDLIBS)

psx06$(EXEEXT): $(psx06_OBJECTS) $(psx06_DEPENDENCIES)
	@rm -f psx06$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
