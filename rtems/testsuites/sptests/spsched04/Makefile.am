##
## $Id: Makefile.am,v 1.23 2009/04/03 12:48:12 ralf Exp $
##

MANAGERS = io rate_monotonic semaphore clock

rtems_tests_PROGRAMS = spsched04
spsched04_SOURCES = init.c getall.c task1.c system.h

dist_rtems_tests_DATA = spsched04.scn
dist_rtems_tests_DATA += spsched04.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spsched04_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spsched04_OBJECTS) $(spsched04_LDADD)
LINK_LIBS = $(spsched04_LDLIBS)

spsched04$(EXEEXT): $(spsched04_OBJECTS) $(spsched04_DEPENDENCIES)
	@rm -f spsched04$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
