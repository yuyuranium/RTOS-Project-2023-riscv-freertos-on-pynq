#include <stdint.h>

#include "uart.h"
#include "printf.h"
#include "common.h"

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

/*
 * Simple trap handler (actually handle nothing)
 */
void simple_trap_handler()
{
    printf("EXCEPTION!!!\n");
    printf("============\n");
    printf("MEPC:   0x%x\n", get_mepc());
    printf("MCAUSE: 0x%x\n", get_mcause());
    printf("MTVAL:  0x%x\n", get_mtval());
    while (1);  // die
}

unsigned int get_mepc()
{
    uint32_t result;
    __asm__ volatile("csrr %0, mepc;" : "=r"(result));
    return result;
}

unsigned int get_mcause()
{
    uint32_t result;
    __asm__ volatile("csrr %0, mcause;" : "=r"(result));
    return result;
}

unsigned int get_mtval()
{
    uint32_t result;
    __asm__ volatile("csrr %0, mtval;" : "=r"(result));
    return result;
}
