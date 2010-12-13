##
## $Id: Makefile.am,v 1.23 2009/04/03 12:48:12 ralf Exp $
##

MANAGERS = io semaphore clock

rtems_tests_PROGRAMS = spsched03
spsched03_SOURCES = init.c task1.c system.h

dist_rtems_tests_DATA = spsched03.scn
dist_rtems_tests_DATA += spsched03.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spsched03_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spsched03_OBJECTS) $(spsched03_LDADD)
LINK_LIBS = $(spsched03_LDLIBS)

spsched03$(EXEEXT): $(spsched03_OBJECTS) $(spsched03_DEPENDENCIES)
	@rm -f spsched03$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
