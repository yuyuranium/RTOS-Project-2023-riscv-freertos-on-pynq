#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#define UART_RX_FIFO  0x0
#define UART_TX_FIFO  0x4
#define UART_STAT_REG 0x8
#define UART_CTRL_REG 0xc

void uart_init();

void uart_putchar(char c);

int uart_getchar();

#endif  // DRIVERS_UART_H_
