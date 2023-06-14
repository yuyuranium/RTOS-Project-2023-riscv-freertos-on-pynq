#include "common.h"
#include "uart.h"
#include "mmio.h"
#include "printf.h"

int main()
{
    uart_init();
    printf("Setting mtimecmp\n");

    // set mtimecmp to 0x10000000
    MMIO_WRITE(0x43c0000c, 0x0);
    MMIO_WRITE(0x43c00008, 0x08000000);

    printf("Enable global interrupt\n");
    // enable global interrupt
    __asm__ volatile("csrs mstatus, 0x8");

    printf("Enable timer interrupt\n");
    // enable mcahine timer interrupt
    __asm__ volatile("li t0, (1 << 7)");
    __asm__ volatile("csrs mie, t0");

    for (;;) {
        unsigned int mtime = MMIO_READ(0x43c00000);
        unsigned int mtimeh = MMIO_READ(0x43c00004);
        unsigned int mtimecmp = MMIO_READ(0x43c00008);
        unsigned int mtimecmph = MMIO_READ(0x43c0000c);
        printf("mtime = 0x%08x%08x, mtimecmp = 0x%08x%08x\r",
               mtimeh, mtime, mtimecmph, mtimecmp);
    }
}

void reset_mtime()
{
    printf("EXCEPTION!!!\n");
    printf("============\n");
    printf("MEPC:   0x%x\n", get_mepc());
    printf("MCAUSE: 0x%x\n", get_mcause());
    printf("MTVAL:  0x%x\n", get_mtval());

    // reset mtime
    printf("RESET MTIME\n");
    MMIO_WRITE(0x43c00004, 0x0);
    MMIO_WRITE(0x43c00000, 0x0);
}
