#ifndef DRIVERS_GPIO_H_
#define DRIVERS_GPIO_H_

#include <stdint.h>

// GPIO is configured as output by default
#define GPIO_DATA  0x0000
#define GPIO_TRI   0x0004

// GPIO2 is configured as input by default
#define GPIO2_DATA 0x0008
#define GPIO2_TRI  0x000c

// GPIO tri-state control
#define GPIO_INPUT  0b1111
#define GPIO_OUTPUT 0b0000

void gpio_init();

uint32_t gpio_read();

void gpio_write(uint32_t data);

uint32_t gpio_read_pin(uint32_t pin);

void gpio_write_pin(uint32_t pin, uint32_t val);

void gpio_toggle_pin(uint32_t pin);

#endif  // DRIVERS_GPIO_H_
