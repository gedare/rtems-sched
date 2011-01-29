##
## $Id: Makefile.am,v 1.23 2009/04/03 12:48:12 ralf Exp $
##

MANAGERS = io rate_monotonic semaphore clock

rtems_tests_PROGRAMS = spsched05
spsched05_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c edfsupport.c system.h edfparams.h edfmacros.h

dist_rtems_tests_DATA = spsched05.scn
dist_rtems_tests_DATA += spsched05.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spsched05_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spsched05_OBJECTS) $(spsched05_LDADD)
LINK_LIBS = $(spsched05_LDLIBS)

spsched05$(EXEEXT): $(spsched05_OBJECTS) $(spsched05_DEPENDENCIES)
	@rm -f spsched05$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
