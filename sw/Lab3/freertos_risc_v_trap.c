#include "FreeRTOS.h"
#include "printf.h"
#include "gpio.h"
#include "semphr.h"

#define LED_RED_PIN    0
#define LED_GREEN_PIN  1
#define LED_ORANGE_PIN 2
#define BTN_BLUE_PIN   0

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0



extern SemaphoreHandle_t xBinarySemaphore;

/*
 * Application exception handler for FreeRTOS
 */
void freertos_risc_v_application_exception_handler( uint32_t cause )
{
    printf("Application Exception Handler Called By FreeRTOS!!!\n");
    printf("MCAUSE: 0x%x\n", cause);
    for ( ; ; ) { } 
    return;
}

/*
 * Application interrupt handler for FreeRTOS
 */
void freertos_risc_v_application_interrupt_handler( uint32_t cause )
{
    // Disable MEIE (bit 11) in MIE Register  
    __asm__ volatile (
        "li     t0, 1<<11\n\t"
        "csrc   mie, t0\n\t" 
    );

    printf("Application Interrupt Handler Called By FreeRTOS!!!\n");
    printf("MCAUSE: 0x%x\n", cause);


	  // Red toggle
    gpio_toggle_pin(LED_RED_PIN);

	  // Give the semaphore to unblock the handler task
	  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	  xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);

	  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    return;
}

