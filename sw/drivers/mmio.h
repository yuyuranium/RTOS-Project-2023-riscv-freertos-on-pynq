#ifndef DRIVERS_MMIO_H_
#define DRIVERS_MMIO_H_

#include <stdint.h>

#define MMIO_WRITE(addr, val) (*((volatile uint32_t *)(addr)) = val)
#define MMIO_READ(addr) (*((volatile uint32_t *)(addr)))

#endif  // DRIVERS_MMIO_H_
