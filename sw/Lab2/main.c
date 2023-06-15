#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "gpio.h"
#include "printf.h"

#define LED_RED_PIN    0
#define LED_GREEN_PIN  1
#define LED_ORANGE_PIN 2

void TaskMonitor_App (void *pvParameters) {
    for ( ; ; ) {
        Taskmonitor();
        vTaskDelay(1000);
    }
}

void Red_LED_App (void *pvParameters) {
    uint32_t Redtimer = 40;
    for ( ; ; ) {
        gpio_toggle_pin(LED_RED_PIN);
        vTaskDelay(Redtimer);
        Redtimer += 1;
    }
}

void Green_LED_App (void *pvParameters) {
    uint32_t Greentimer = 50;
    for ( ; ; ) {
        gpio_toggle_pin(LED_GREEN_PIN);
        vTaskDelay(Greentimer);
        Greentimer += 2;
    }
}

void Delay_App (void *pvParameters) {
    int delayflag = 0;
    uint32_t delaytime;
    while (1) {
        if ( delayflag == 0 ) {
            delaytime = 100;
            delayflag = 1;
        } else {
            delaytime = 0xFFFFFFFF;
        }
        vTaskDelay(delaytime);
    }
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    gpio_init();

    xTaskCreate (
        Red_LED_App,
        "Red_LED_App",
        256,
        NULL,
        1,
        NULL );

    xTaskCreate (
        Green_LED_App,
        "Green_LED_App",
        256,
        NULL,
        1,
        NULL );

    xTaskCreate (
        Delay_App,
        "Delay_App",
        256,
        NULL,
        14,
        NULL );

    xTaskCreate (
        TaskMonitor_App,
        "TaskMonitor_App",
        256,
        NULL,
        3,
        NULL );

    vTaskStartScheduler();
    /* Infinite loop */
    while (1) { }
}
