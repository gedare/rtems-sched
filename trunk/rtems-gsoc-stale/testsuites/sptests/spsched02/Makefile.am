##
## $Id: Makefile.am,v 1.3 2009/07/30 17:10:04 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spsched02
spsched02_SOURCES = init.c

dist_rtems_tests_DATA = spsched02.scn
dist_rtems_tests_DATA += spsched02.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spsched02_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spsched02_OBJECTS) $(spsched02_LDADD)
LINK_LIBS = $(spsched02_LDLIBS)

spsched02$(EXEEXT): $(spsched02_OBJECTS) $(spsched02_DEPENDENCIES)
	@rm -f spsched02$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
