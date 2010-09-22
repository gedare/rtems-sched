/*
 * traptable.h
 *
 * Copyright 2010 Gedare Bloom
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 * $Id: traptable.h,v 1.2 2010/08/26 18:04:51 joel Exp $
 */

/* This file can be included by assembly code */

#define ENTRY_SIZE (32)

#define TABLE_SIZE (1024*ENTRY_SIZE * 2 /* HACK */ )

#ifndef ASM
extern void* trap_table[TABLE_SIZE];
#endif

