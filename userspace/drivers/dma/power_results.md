# Lab 8: DMA, CPU Frequency and Power

Fill in this table from the output of `dma_benchmarking`, run once at each CPU
frequency (see the Lab 8 page). Report times in seconds, to three decimal places.

| Mode                           | 650 MHz Elapsed | 650 MHz CPU | 325 MHz Elapsed | 325 MHz CPU |
|--------------------------------|-----------------|-------------|-----------------|-------------|
| CPU draws the sprites          |                 |             |                 |             |
| DMA, CPU polls in a tight loop |                 |             |                 |             |
| DMA, CPU sleeps between checks |                 |             |                 |             |

## Questions

Answer each in two or three sentences.

1. When the CPU frequency is halved, the time for the CPU to draw the sprites
   changes much more than the time for the DMA to copy them. Why?

2. Compare the CPU time of the two DMA modes. What is the CPU doing in each case,
   and what does that mean for how much power the processor uses while the DMA
   works?

3. Compare "DMA, CPU sleeps between checks" at 325 MHz with "CPU draws the
   sprites" at 650 MHz. What does this suggest about designing a low-power
   embedded system?

### Answers

1.

2.

3.
