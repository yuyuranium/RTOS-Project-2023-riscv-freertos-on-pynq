#include <stdint.h>

#include "gpio.h"
#include "mmio.h"
#include "mmap_regs.h"

void gpio_init()
{
    // GPIO is configured as output by default
    MMIO_WRITE(GPIO_BASE + GPIO_TRI, GPIO_OUTPUT);

    // GPIO2 is configured as input by default
    MMIO_WRITE(GPIO_BASE + GPIO2_TRI, GPIO_INPUT);
}

uint32_t gpio_read()
{
    uint32_t data = MMIO_READ(GPIO_BASE + GPIO2_DATA);
    return data;
}

void gpio_write(uint32_t data)
{
    MMIO_WRITE(GPIO_BASE + GPIO_DATA, data);
}


uint32_t gpio_read_pin(uint32_t pin)
{
    uint32_t data = gpio_read();
    data = (data >> pin) & 0b1;
    return data;
}

void gpio_write_pin(uint32_t pin, uint32_t val)
{
    uint32_t data = gpio_read();
    if (val) {
        // set the corresponding bit
        data |= (0b1 << pin);
    } else {
        // clear the corresponding bit
        data &= ~(0b1 << pin);
    }
    gpio_write(data);
}

void gpio_toggle_pin(uint32_t pin)
{
    uint32_t data = gpio_read();
    // toggle the corresponding bit
    data ^= (0b1 << pin);
    gpio_write(data);
}
