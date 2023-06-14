#include "FreeRTOS.h"
#include "task.h"
#include "printf.h"

#define STACK_SIZE 1024

/* Task to be created. */
void vTaskTest( void * pvParameters )
{
    for( ;; )
    {
        vTaskDelay(1000);
        printf("hello\n");
    }
}

void vTaskTest2( void * pvParameters )
{
    for( ;; )
    {
        vTaskDelay(2000);
        printf("world\n");
    }
}

int main()
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;
    TaskHandle_t xHandle2 = NULL;

    printf("Create task\n");

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    vTaskTest,       /* Function that implements the task. */
                    "Test",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    NULL,            /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */

    if( xReturned != pdPASS )
    {
        printf("Task create fail\n");
        goto dead;
    }

    xReturned = xTaskCreate(
                    vTaskTest2,      /* Function that implements the task. */
                    "Test",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    NULL,            /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &xHandle2 );     /* Used to pass out the created task's handle. */

    if( xReturned != pdPASS )
    {
        printf("Task create fail\n");
        goto dead;
    }

    vTaskStartScheduler();

dead:
    while (1);
    /* Should never get here! */
    return 0;
}
