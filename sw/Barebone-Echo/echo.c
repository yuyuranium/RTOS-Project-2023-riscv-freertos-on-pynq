#include "printf.h"
#include "uart.h"
#include "mmio.h"

void readline(char *buf)
{
    char c;
    for (;;) {
        c = uart_getchar();
        *(buf++) = c;

        // check if `return` is pressed
        if (c == 13) {
            *buf = 0;
            break;
        }
    }
}

int main()
{
    uart_init();
    for (;;) {
        char buf[128];
        printf("Enter: ");
        readline(buf);
        printf("You entered: %s\n", buf);
    }
}

