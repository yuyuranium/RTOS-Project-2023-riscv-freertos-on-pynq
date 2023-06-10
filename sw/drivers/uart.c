#include <stdint.h>

#include "mmap_regs.h"
#include "mmio.h"
#include "uart.h"

void uart_init()
{
    // reset rx and tx fifo
    uint32_t data = 0b00011;
    MMIO_WRITE(UART_BASE + UART_CTRL_REG, data);
}

void uart_putchar(char c)
{
    // busy waiting until tx fifo has room
    while ((MMIO_READ(UART_BASE + UART_STAT_REG) >> 3) & 0b1);
    MMIO_WRITE(UART_BASE + UART_TX_FIFO, c);
}

int uart_getchar()
{
    // busy waiting until rx fifo has data to read
    while (MMIO_READ(UART_BASE + UART_STAT_REG) & 0b1);
    return MMIO_READ(UART_BASE + UART_RX_FIFO);
}
