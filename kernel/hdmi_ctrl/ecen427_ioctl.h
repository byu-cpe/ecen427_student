/*
 * The information in this header is broken out into its own file so that it
 *  can also be included in userspace programs
 */

#ifndef __ECEN427_IOCTL_H
#define __ECEN427_IOCTL_H

#include <linux/ioctl.h>

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
typedef uint32_t __u32;
typedef uint32_t u32;
#endif

/********************************** structs ***********************************/
// structs for the reconfiguring of vdma and dynClk
struct ecen427_vdma_reconfig_st {
  u32 hsize;
  u32 vsize;
};

struct ecen427_clockConfig_st {
  u32 clk0L;
  u32 clkFBL;
  u32 clkFBH_clk0H;
  u32 divclk;
  u32 lockL;
  u32 fltr_lockH;
};

/***************************** IOCTl information ******************************/
// each device that supports IOCTL must have a "magic" number (char) that
//  identifies it. Choose to avoid naming collisions as much as possible
#define ECEN427_IOC_MAGIC 'j' // joystick - probably not used on a Pynq
#define ECEN427_IOC_CONFIG_VDMA                                                \
  _IOW(ECEN427_IOC_MAGIC, 1, struct ecen427_vdma_reconfig_st *)
#define ECEN427_IOC_CONFIG_VTC _IOW(ECEN427_IOC_MAGIC, 2, __u32)
#define ECEN427_IOC_CONFIG_DYNCLK                                              \
  _IOW(ECEN427_IOC_MAGIC, 3, struct ecen427_clockConfig_st *)
#define ECEN427_IOC_RESET _IO(ECEN427_IOC_MAGIC, 4)
#define ECEN427_IOC_WRITE_PINK _IO(ECEN427_IOC_MAGIC, 5)
#define ECEN427_IOC_FRAME_BUFFER_ADDR _IOR(ECEN427_IOC_MAGIC, 6, __u32)

#endif /* __ECEN427_IOCTL_H */
