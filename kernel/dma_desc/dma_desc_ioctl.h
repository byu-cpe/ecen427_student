#ifndef DMA_DESC_DMA_DESC_IOCTL_H
#define DMA_DESC_DMA_DESC_IOCTL_H

#include <linux/ioctl.h>

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
typedef uint32_t __u32;
typedef uint32_t u32;
#endif

#define DMA_DESC_IOC_MAGIC 'd'
#define DMA_DESC_IOC_BUFFER_ADDR _IOR(DMA_DESC_IOC_MAGIC, 1, __u32)

#endif /* DMA_DESC_DMA_DESC_IOCTL_H */
