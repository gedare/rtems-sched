##
## $Id: Makefile.am,v 1.22 2010/08/23 07:38:50 sh Exp $
##

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h
DISTCLEANFILES = include/bspopts.h

noinst_PROGRAMS =

noinst_LIBRARIES = libbspstart.a
libbspstart_a_SOURCES = startup/start.S
project_lib_DATA = start.$(OBJEXT)

libbspstart_a_SOURCES += ../shared/start/rtems_crti.S
project_lib_DATA += rtems_crti.$(OBJEXT)

# Link commands
dist_project_lib_DATA += startup/linkcmds.gwlcfm  startup/linkcmds.mpc5566evb \
	startup/linkcmds.base	

noinst_LIBRARIES += libbsp.a
libbsp_a_SOURCES =

# Includes
include_HEADERS = include/bsp.h
include_HEADERS += ../../shared/include/tm27.h

nodist_include_HEADERS = include/bspopts.h ../../shared/tod.h \
    ../../shared/include/coverhd.h
include_bsp_HEADERS = include/mpc55xxevb.h \
    include/smsc9218i.h \
    ../../shared/include/irq-generic.h \
    ../../shared/include/irq-info.h \
    ../../shared/include/utility.h \
    ../shared/include/tictac.h

# startup
libbsp_a_SOURCES += ../../shared/bsplibc.c ../../shared/bsppost.c \
    ../../shared/bootcard.c ../shared/src/tictac.c ../../shared/bspclean.c \
    ../shared/startup/bspidle.c startup/bspstart.c startup/bspgetworkarea.c \
    ../../shared/bsppretaskinghook.c

# clock
libbsp_a_SOURCES += clock/clock-config.c

# irq_generic
libbsp_a_SOURCES += ../../shared/src/irq-generic.c \
    ../../shared/src/irq-legacy.c \
    ../../shared/src/irq-info.c \
    ../../shared/src/irq-shell.c

# Misc
libbsp_a_SOURCES += startup/sd-card-init.c

# bsp_i2c
libbsp_a_SOURCES += i2c/i2c_init.c

# Network
if HAS_NETWORKING
noinst_PROGRAMS += network.rel
network_rel_SOURCES = network/smsc9218i.c
network_rel_CPPFLAGS = $(AM_CPPFLAGS) -D__INSIDE_RTEMS_BSD_TCPIP_STACK__ -D__BSD_VISIBLE
network_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)
endif

# BSP library

libbsp_a_LIBADD = ../../../libcpu/@RTEMS_CPU@/shared/cpuIdent.rel \
    ../../../libcpu/@RTEMS_CPU@/shared/cache.rel \
    ../../../libcpu/@RTEMS_CPU@/shared/stack.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/misc.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/irq.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/siu.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/edma.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/emios.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/dspi.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/esci.rel \
    ../../../libcpu/@RTEMS_CPU@/@exceptions@/rtems-cpu.rel \
    ../../../libcpu/@RTEMS_CPU@/@exceptions@/exc_bspsupport.rel \
    ../../../libcpu/@RTEMS_CPU@/@RTEMS_CPU_MODEL@/timer.rel
if HAS_NETWORKING
libbsp_a_LIBADD += network.rel
endif

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
