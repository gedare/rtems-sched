##
##  $Id: Makefile.am,v 1.24 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = paranoia
paranoia_SOURCES = init.c paranoia.c system.h

dist_rtems_tests_DATA = paranoia.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

paranoia_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

#  -DCYGNUS   turns on more verbose msgs
AM_CPPFLAGS += -DNOSIGNAL -DCYGNUS -DNOMAIN

paranoia_LDLIBS = -lm

LINK_OBJS = $(paranoia_OBJECTS) $(paranoia_LDADD)
LINK_LIBS = $(paranoia_LDLIBS)

paranoia$(EXEEXT): $(paranoia_OBJECTS) $(paranoia_DEPENDENCIES)
	@rm -f paranoia$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
