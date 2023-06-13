#include "printf.h"
#include "uart.h"

int main()
{
    uart_init();
    for (;;) {
        printf("Hello!\n");
    }
}
