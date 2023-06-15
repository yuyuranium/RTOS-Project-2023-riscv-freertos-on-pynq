#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "gpio.h"

#define LED_RED_PIN    0
#define LED_GREEN_PIN  1
#define LED_ORANGE_PIN 2
#define BTN_BLUE_PIN   0

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0

QueueHandle_t xQueue1;

static void pvLedTask(void *p)
{
	// 0: red
	// 1: green
	// 2: after red
	// 3: after green
	// 4: orange
	// 5: after orange
	int state = 0;
	int nstate[6] = {2, 3, 1, 0, 5, 4};
	int msg;
	for (;;) {
		switch (state) {
		case 0:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_SET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		case 1:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_SET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		case 2:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		case 3:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		case 4:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_SET);
			break;
		case 5:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		default:
			gpio_write_pin(LED_RED_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_GREEN_PIN, GPIO_PIN_RESET);
			gpio_write_pin(LED_ORANGE_PIN, GPIO_PIN_RESET);
			break;
		}
		vTaskDelay(500);

		msg = 0;
		xQueueReceive(xQueue1, &msg, (TickType_t)0);
		if (msg) {
			state = (state < 4) ? 4 : 0;
		} else {
			state = nstate[state];
		}
	}
}

static void pvBtnTask(void *p)
{
	for (;;) {
        if (gpio_read_pin(BTN_BLUE_PIN)) {
            int data = 1;
            xQueueSend(xQueue1, (void *)&data, (TickType_t)10);
            vTaskDelay(200);
        }
	}
}

int main(void)
{
    gpio_init();

    xQueue1 = xQueueCreate(1, sizeof(int));

    xTaskCreate(
        pvLedTask,
        "LedTask",
        512,
        NULL,
        1,
        NULL);

    xTaskCreate(
        pvBtnTask,
        "BtnTask",
        512,
        NULL,
        1,
        NULL);

    vTaskStartScheduler();

    /* Infinite loop */
    while (1) { }
}
