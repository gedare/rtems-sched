##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin23
spspin23_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin23.scn
dist_rtems_tests_DATA += spspin23.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin23_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin23_OBJECTS) $(spspin23_LDADD)
LINK_LIBS = $(spspin23_LDLIBS)

spspin23$(EXEEXT): $(spspin23_OBJECTS) $(spspin23_DEPENDENCIES)
	@rm -f spspin23$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
