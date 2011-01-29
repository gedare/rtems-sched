/*
 *  This routine is an implementation of the bsp_get_work_area()
 *  that can be used by all BSPs following linkcmds conventions
 *  regarding heap, stack, and workspace allocation.
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: bspgetworkarea.c,v 1.1 2010/06/17 16:20:46 joel Exp $
 */

#include <bsp.h>
#include <bsp/bootcard.h>
#ifdef BSP_GET_WORK_AREA_DEBUG
  #include <rtems/bspIo.h>
#endif

/*
 *  These are provided by the linkcmds for ALL of the BSPs which use this file.
 */
extern char WorkAreaBase[];
extern char HeapSize[];
extern char HeapBase[];
extern char StackSize[];
extern char end[];

extern char RamBase[];
extern char RamSize[];

/*
 *  This method returns the base address and size of the area which
 *  is to be allocated between the RTEMS Workspace and the C Program
 *  Heap.
 */
void bsp_get_work_area(
  void      **work_area_start,
  uintptr_t  *work_area_size,
  void      **heap_start,
  uintptr_t  *heap_size
)
{
  uintptr_t ram_end;

  ram_end = (uintptr_t)RamBase + (uintptr_t)RamSize;

  *work_area_start = &end;
  *work_area_size  = (void*)((void*)ram_end - (void*)&end) - (void*)StackSize;
  *heap_start      = BSP_BOOTCARD_HEAP_USES_WORK_AREA;
  *heap_size       = BSP_BOOTCARD_HEAP_SIZE_DEFAULT;

  /*
   *  The following may be helpful in debugging what goes wrong when
   *  you are allocating the Work Area in a new BSP.
   */
  #ifdef BSP_GET_WORK_AREA_DEBUG
    {
      void *sp = __builtin_frame_address(0);
      void *end = *work_area_start + *work_area_size;
      printk(
		"bsp_get_work_area\n\r"
        "work_area_start = 0x%p\n\r"
        "work_area_size = %d 0x%08x\n\r"
        "end = 0x%p\n\r"
        "heap_start = 0x%p\n\r"
        "heap_size = %d\n\r"
        "current stack pointer = 0x%p%s\n\r",
        *work_area_start,
        *work_area_size,  /* decimal */
        *work_area_size,  /* hexadecimal */
        end,
        *heap_start,
        *heap_size,
        sp,
        ((sp >= *work_area_start && sp <= end) ? " OVERLAPS!" : "")
     );
  }
 #endif
}
