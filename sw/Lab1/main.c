#include "printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



#define granularity 1
QueueHandle_t xQueue1; //xHandle;

int sendDelay = 110;
int green = 0, red = 0, orange = 0; 

void print_light() {
  char output[30];
  char *a = output;

  if (green) {
    *a++=' '; *a++='g'; *a++='r' ; *a++='e' ; *a++='e' ; *a++='n' ; *a++=',' ; *a++=' ' ;
  }
  else {
    *a++='x'; *a++='x'; *a++='x' ; *a++='x' ; *a++='x' ; *a++='x' ; *a++=',' ; *a++=' ' ;
  }
    
  if (red) {
    *a++=' '; *a++=' '; *a++=' ' ; *a++='r' ; *a++='e' ; *a++='d' ; *a++=',' ; *a++=' ' ;
  }
  else {
    *a++='x'; *a++='x'; *a++='x' ; *a++='x' ; *a++='x' ; *a++='x' ; *a++=',' ; *a++=' ' ;
  }

  if (orange){
    *a++='o'; *a++='r'; *a++='a' ; *a++='n' ; *a++='g' ; *a++='e' ;
  }
  else {
    *a++='x'; *a++='x'; *a++='x' ; *a++='x' ; *a++='x' ; *a++='x' ;
  }

  *a++='\0';

  printf("%s\n", output);
}

void LEDTask_APP (void *pvParameters) {

	int message = 0;
	int state = 0;
	int counter0 = 16 / granularity - 3;
	int counter1 = 9 / granularity - 1;

	/* Infinite loop */
	for ( ; ; ) {
		if (state == 0) {
			//HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
      green = 1;
      print_light();
			for (int i = 0 ; i < counter0 ; i++) {
				vTaskDelay(granularity);
				if ( xQueueReceive(	xQueue1, &(message), ((TickType_t) 0)) == pdPASS ) {
					if (message) {
						message = 0;
						//HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            green = 0;
            //print_light();
						state = 1;
						break;
					}
				}
			}
			if (state == 1) continue;
			//HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			//HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
      green=0; red=1;
      print_light();
			for (int i = 0 ; i < counter0 ; i++) {
				vTaskDelay(granularity);
				if ( xQueueReceive(	xQueue1, &(message), ((TickType_t) 0)) == pdPASS ) {
					if (message) {
						message = 0;
						//HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            red = 0;
            //print_light();
						state = 1;
						break;
					}
				}
			}
			if (state == 1) continue;
			//HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
      red = 0;
      //print_light();
		}
		else {
			//HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
      orange = 1;
      print_light();
			for (int i = 0 ; i < counter1 ; i++) {
				vTaskDelay(granularity);
				if ( xQueueReceive(	xQueue1, &(message), ((TickType_t) 0)) == pdPASS ) {
					if (message) {
						message = 0;
						//HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
            orange = 0;
            //print_light();
						state = 0;
						break;
					}
				}
			}
			if (state == 0) continue;
			//HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
      orange = 0;
      print_light();
			for (int i = 0 ; i < counter1 ; i++) {
				vTaskDelay(granularity);
				if ( xQueueReceive(	xQueue1, &(message), ((TickType_t) 0)) == pdPASS ) {
					if (message) {
						message = 0;
						state = 0;
						break;
					}
				}
			}
			if (state == 0) continue;
		}
	}
}

void BUTTONTask_APP (void *pvParameters) {
	for ( ; ; ) {
	//	if ( HAL_GPIO_ReadPin(BTN_BLUE_GPIO_Port, BTN_BLUE_Pin) == GPIO_PIN_SET ) {
      vTaskDelay(sendDelay);
			xQueueSend(	xQueue1, (void *) 1, ((TickType_t) 0));
      if (sendDelay == 50)
        sendDelay = 110;
      else
        sendDelay -= 10;
			//while (HAL_GPIO_ReadPin(BTN_BLUE_GPIO_Port, BTN_BLUE_Pin) == GPIO_PIN_SET);
			//vTaskDelay(150);
	//	}
	}
}



int main(void)
{
  /* USER CODE BEGIN SysInit */
  xTaskCreate (
	    LEDTask_APP,
		  "LEDTask_APP",
		  512,
		  NULL,
		  1,
		  NULL );

  xTaskCreate (
  	  BUTTONTask_APP,
  	  "BUTTONTask_APP",
  	  512,
  	  NULL,
  	  1,
  	  NULL );

  xQueue1 = xQueueCreate (1, sizeof(int) );
  /* USER CODE END SysInit */

  vTaskStartScheduler();

  /* Infinite loop */
  while (1) { }
}
