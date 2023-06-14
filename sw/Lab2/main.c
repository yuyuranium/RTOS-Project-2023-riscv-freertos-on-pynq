#include "printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"




///////////////////////////////////////////////////////////////////////////
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





//UART_HandleTypeDef huart2;


void TaskMonitor_App (void *pvParameters) {
	for ( ; ; ) {
		Taskmonitor();
		vTaskDelay(20);
	}
}

void Red_LED_App (void *pvParameters) {
	uint32_t Redtimer = 40;
	for ( ; ; ) {
		//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    red = red ^ 0b1;
    //print_light();
		vTaskDelay(Redtimer);
		Redtimer += 1;
	}
}

void Green_LED_App (void *pvParameters) {
	uint32_t Greentimer = 50;
	for ( ; ; ) {
		//HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
    green = green ^ 0b1;
    //print_light();
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


/*UART_HandleTypeDef huart2;
void USART_Test (void *pvParameters) {
	uint32_t Monitortimer = 400;
	char MonitorTset[30];
	char num[15];
	int i = 0;
	while (1) {
		memset(MonitorTset, '\0', sizeof(MonitorTset));
		memset(num, '\0', sizeof(num));
		itoa(i, num, 10);
		strcat(num, " ");
		sprintf(MonitorTset, "The point is %s\n\r", num);
		HAL_UART_Transmit(
			&huart2,
			(uint8_t *) MonitorTset,
			strlen(MonitorTset),
			0xffff
		);
		vTaskDelay(Monitortimer);
		Monitortimer += 1;
		i += 1;
	}
}
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

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
