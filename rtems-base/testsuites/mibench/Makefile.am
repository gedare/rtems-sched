##
## $Id$
##

ACLOCAL_AMFLAGS = -I ../aclocal

SUBDIRS = bitcount_large bitcount_small crc dijkstra sha_small \
					susan_corners susan_edges susan_smoothing
#	dijkstra_small_sort dijkstra_large_sort \
#	dijkstra_small_sort_HWPQ dijkstra_large_sort_HWPQ

if MPTESTS
endif

if CXXTESTS
endif

if NETTESTS
endif

include $(top_srcdir)/../automake/subdirs.am
include $(top_srcdir)/../automake/local.am
