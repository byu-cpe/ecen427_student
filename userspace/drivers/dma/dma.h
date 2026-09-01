#ifndef DRIVERS_DMA_DMA_H
#define DRIVERS_DMA_DMA_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DMA_SUCCESS 0

int32_t dma_init();
void dma_exit();

// Use the AXI CDMA to copy a sprite from one location to another
// src_x, src_y: the top-left corner of the sprite to copy
// dest_x, dest_y: the top-left corner of the destination
// width, height: the width and height of the sprite
void dma_start_sprite_copy(uint16_t src_x, uint16_t src_y, uint16_t dest_x,
                           uint16_t dest_y, uint16_t width, uint16_t height);

// Check if the DMA is currently busy
bool dma_is_busy();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_DMA_DMA_H */
