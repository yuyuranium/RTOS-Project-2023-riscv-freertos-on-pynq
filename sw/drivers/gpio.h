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
#define GPIO_INPUT  -1
#define GPIO_OUTPUT 0

// Configure GPIO as output and GPIO2 as input
void gpio_init();

// General method to read the value from `gpio` register
uint32_t gpio_read(void *gpio);

// General method to write the value to `gpio` register
void gpio_write(void *gpio, uint32_t data);

// Read a pin value from GPIO2
uint32_t gpio_read_pin(uint32_t pin);

// Write a pin value to GPIO
void gpio_write_pin(uint32_t pin, uint32_t val);

// Toggle a pin value to GPIO
void gpio_toggle_pin(uint32_t pin);

#endif  // DRIVERS_GPIO_H_
