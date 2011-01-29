##
## $Id: Makefile.am,v 1.1 2010/12/06 16:35:30 joel Exp $
##

ACLOCAL_AMFLAGS = -I ../aclocal

if HAS_POSIX
SUBDIRS = \
    psxtmmutex02 \
    psxtmthread01 psxtmthread03
endif

DIST_SUBDIRS = $(SUBDIRS)
# EXTRA_DIST = psxfatal_support/init.c psxfatal_support/system.h

include $(top_srcdir)/../automake/subdirs.am
include $(top_srcdir)/../automake/local.am
