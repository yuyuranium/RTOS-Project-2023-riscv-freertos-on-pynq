#include "printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "gpio.h"
#include "mmio.h"


#define LED_RED_PIN    0
#define LED_GREEN_PIN  1
#define LED_ORANGE_PIN 2
#define BTN_BLUE_PIN   0

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0

SemaphoreHandle_t xBinarySemaphore;


uint32_t get_time() 
{
    uint32_t mtime = MMIO_READ(0x43c00000);

    return mtime;
}


void Green_LED_Task(void *pvParameters)
{
    // Green Blinking
    for( ; ; ) {
        gpio_toggle_pin(LED_GREEN_PIN);
        vTaskDelay(1000);
    }
}


void vHandlerTask( void *pvParameters )
{

    for( ; ; ) {
        // Take the semaphore
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);

        // Semaphore was obtained

        // Orange Blinks 5 times
        for (int i = 0 ; i < 10 ; i++) {
            uint32_t From_begin_time = get_time();
            gpio_toggle_pin(LED_ORANGE_PIN);
            while(get_time() - From_begin_time < 7000000);
        }

        // Reset interrupt register
        __asm__ volatile (
        "li     t0, 1<<11\n\t"
            "csrs   mie, t0\n\t" 
        );
    }
}


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    // Create the semaphore //
    xBinarySemaphore = xSemaphoreCreateBinary();

    if (xBinarySemaphore == NULL)
        return 0;

    // Initialize gpio
    gpio_init();

    // task create //
    xTaskCreate (
        Green_LED_Task,
        "Green_LED_Task",
        256,
        NULL,
        1,
        NULL );

    xTaskCreate (
        vHandlerTask,
        "vHandlerTask",
        256,
        NULL,
        3,
        NULL );

    // Start Scaheduler
    vTaskStartScheduler();

    // Infinite loop
    while (1) { }
}

