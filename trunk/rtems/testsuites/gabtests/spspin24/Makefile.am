##
##  $Id: Makefile.am,v 1.26 2009/08/26 13:22:58 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spspin24
spspin24_SOURCES = init.c tasks_periodic.c tasks_aperiodic.c params.h macros.h system.h

dist_rtems_tests_DATA = spspin24.scn
dist_rtems_tests_DATA += spspin24.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spspin24_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spspin24_OBJECTS) $(spspin24_LDADD)
LINK_LIBS = $(spspin24_LDLIBS)

spspin24$(EXEEXT): $(spspin24_OBJECTS) $(spspin24_DEPENDENCIES)
	@rm -f spspin24$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
