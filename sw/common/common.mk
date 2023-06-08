#########################
# RISC-V GCC toolchains #
#########################
RISCV_PREFIX   = ~/.local/lowrisc-toolchain-gcc-rv32imcb-20230427-1/bin/riscv32-unknown-elf-
AR             = $(RISCV_PREFIX)ar
CC             = $(RISCV_PREFIX)gcc
OBJDUMP        = $(RISCV_PREFIX)objdump
OBJCOPY        = $(RISCV_PREFIX)objcopy
READELF        = $(RISCV_PREFIX)readelf
RISCV_GCC_OPTS = -march=rv32imcb -mabi=ilp32 -mcmodel=medany -nostartfiles -nostdlib

###########
# Sources #
###########

ifndef PROGRAM
$(error "Must define PROGRAM first")
endif

# root of the sw directory
SW_ROOT ?= $(shell cd .. && pwd)

# root to FreeRTOS & printf sources
FREERTOS_SOURCE_DIR = $(SW_ROOT)/FreeRTOS
PRINTF_SOURCE_DIR   = $(SW_ROOT)/printf
COMMON_SOURCE_DIR   = $(SW_ROOT)/common
DRIVER_SOURCE_DIR   = $(SW_ROOT)/drivers
PROGRAM_SOURCE_DIR  = $(SW_ROOT)/$(PROGRAM)

# use heap_5 by default
HEAP_CONFIG ?= 5

# collect all FreeRTOS sources
FREERTOS_SRC = \
    $(FREERTOS_SOURCE_DIR)/croutine.c \
    $(FREERTOS_SOURCE_DIR)/list.c \
    $(FREERTOS_SOURCE_DIR)/queue.c \
    $(FREERTOS_SOURCE_DIR)/tasks.c \
    $(FREERTOS_SOURCE_DIR)/timers.c \
    $(FREERTOS_SOURCE_DIR)/stream_buffer.c \
    $(FREERTOS_SOURCE_DIR)/event_groups.c \
    $(FREERTOS_SOURCE_DIR)/portable/MemMang/heap_$(HEAP_CONFIG).c

# collect printf source
PRINTF_SRC = $(PRINTF_SOURCE_DIR)/printf.c

# collect common sources
PORT_SRC = \
		$(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V/port.c \
    $(COMMON_SOURCE_DIR)/common.c

# collect all assembly codes
PORT_ASM = \
		$(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V/portASM.S \
    $(COMMON_SOURCE_DIR)/crt0.S

# collect all driver codes
DRIVER_SRC = \
		$(DRIVER_SOURCE_DIR)/gpio.c \
		$(DRIVER_SOURCE_DIR)/uart.c

# collect all program sources
PROGRAM_SRC = $(wildcard $(PROGRAM_SOURCE_DIR)/*.c)

####################
# Compiler options #
####################
# setup include paths
INCLUDES = \
    -I$(FREERTOS_SOURCE_DIR)/include \
		-I$(FREERTOS_SOURCE_DIR)/portable/GCC/RISC-V \
    -I$(PRINTF_SOURCE_DIR) \
    -I$(COMMON_SOURCE_DIR) \
    -I$(DRIVER_SOURCE_DIR) \
		-I$(PROGRAM_SOURCE_DIR)

# setup flags
CFLAGS  = -O2 -g -Wall $(INCLUDES) $(RISCV_GCC_OPTS)
LDFLAGS = -L. -T $(SW_ROOT)/common/link.ld $(RISCV_GCC_OPTS)
LIBS    = -lm -lc -lgcc

###########
# Targets #
###########
# convert all sources to objects
FREERTOS_OBJ = $(FREERTOS_SRC:.c=.o)
PRINTF_OBJ   = $(PRINTF_SRC:.c=.o)
PORT_OBJ     = $(PORT_SRC:.c=.o) $(PORT_ASM:.S=.o)
DRIVER_OBJ   = $(DRIVER_SRC:.c=.o)
PROGRAM_OBJ  = $(PROGRAM_SRC:.c=.o)
OBJS         = $(FREERTOS_OBJ) $(PRINTF_OBJ) $(PORT_OBJ) $(DRIVER_OBJ) $(PROGRAM_OBJ)

# determine output files
OUTFILES := $(PROGRAM).elf $(PROGRAM).dis $(PROGRAM).bin

###########
# Recipes #
###########

.PHONY: all clean

all: $(OUTFILES)

$(PROGRAM).elf: $(OBJS) $(LINKER_SCRIPT)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS)

$(PROGRAM).dis: $(PROGRAM).elf
	$(OBJDUMP) -xsd $< > $@

$(PROGRAM).bin: $(PROGRAM).elf
	$(OBJCOPY) -O binary $^ $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(OUTFILES)
