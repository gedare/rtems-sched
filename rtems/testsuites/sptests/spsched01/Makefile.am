##
## $Id: Makefile.am,v 1.23 2009/04/03 12:48:12 ralf Exp $
##

MANAGERS = io semaphore clock

rtems_tests_PROGRAMS = spsched01
spsched01_SOURCES = init.c task1.c system.h

dist_rtems_tests_DATA = spsched01.scn
dist_rtems_tests_DATA += spsched01.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spsched01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spsched01_OBJECTS) $(spsched01_LDADD)
LINK_LIBS = $(spsched01_LDLIBS)

spsched01$(EXEEXT): $(spsched01_OBJECTS) $(spsched01_DEPENDENCIES)
	@rm -f spsched01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
