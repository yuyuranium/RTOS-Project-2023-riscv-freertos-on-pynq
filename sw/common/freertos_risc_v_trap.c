#include "FreeRTOS.h"
#include "printf.h"

/*
 * Application exception handler for FreeRTOS
 */
void freertos_risc_v_application_exception_handler( uint32_t cause )
{
    printf("Application Exception Handler Called By FreeRTOS!!!\n");
    printf("MCAUSE: 0x%x\n", cause);
    return;
}

/*
 * Application interrupt handler for FreeRTOS
 */
void freertos_risc_v_application_interrupt_handler( uint32_t cause )
{
    printf("Application Interrupt Handler Called By FreeRTOS!!!\n");
    printf("MCAUSE: 0x%x\n", cause);
    return;
}
