##
## $Id$
##

ACLOCAL_AMFLAGS = -I ../aclocal

SUBDIRS = basicmath_large basicmath_small bitcount_large bitcount_small \
					crc dijkstra \
					fft_small fft_large fftinv_small fftinv_large \
					qsort_small sha_small \
					stringsearch_large stringsearch_small \
					susan_corners susan_edges susan_smoothing
#	dijkstra_small_sort dijkstra_large_sort \
#	dijkstra_small_sort_HWPQ dijkstra_large_sort_HWPQ

if MPTESTS
endif

if CXXTESTS
endif

if NETTESTS
SUBDIRS += patricia_small
endif

include $(top_srcdir)/../automake/subdirs.am
include $(top_srcdir)/../automake/local.am
