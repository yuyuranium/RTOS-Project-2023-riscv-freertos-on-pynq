#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "uart.h"
#include "printf.h"

/*
 * Basic function for the system to output a character, used by printf.c
 */
void _putchar(char character)
{
    if (character == '\n') {
        uart_putchar('\r');
    }
    uart_putchar(character);
}
