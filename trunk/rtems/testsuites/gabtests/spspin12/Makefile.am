##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin12
spspin12_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin12.scn
dist_rtems_tests_DATA += spspin12.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin12_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin12_OBJECTS) $(spspin12_LDADD)
LINK_LIBS = $(spspin12_LDLIBS)

spspin12$(EXEEXT): $(spspin12_OBJECTS) $(spspin12_DEPENDENCIES)
	@rm -f spspin12$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
