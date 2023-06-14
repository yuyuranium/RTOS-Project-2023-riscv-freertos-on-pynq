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

# root to sources
PRINTF_SOURCE_DIR   = $(SW_ROOT)/printf
COMMON_SOURCE_DIR   = $(SW_ROOT)/common
DRIVER_SOURCE_DIR   = $(SW_ROOT)/drivers
PROGRAM_SOURCE_DIR  = $(SW_ROOT)/$(PROGRAM)

# collect printf source
PRINTF_SRC = $(PRINTF_SOURCE_DIR)/printf.c

# collect common sources
PORT_SRC = \
	$(COMMON_SOURCE_DIR)/common.c

# collect all assembly codes
PORT_ASM = \
	$(COMMON_SOURCE_DIR)/crt0.S

# collect all driver codes
DRIVER_SRC = \
	$(DRIVER_SOURCE_DIR)/gpio.c \
	$(DRIVER_SOURCE_DIR)/uart.c

# collect all program sources
PROGRAM_SRC = $(wildcard $(PROGRAM_SOURCE_DIR)/*.c)
PROGRAM_ASM = $(wildcard $(PROGRAM_SOURCE_DIR)/*.S)

####################
# Compiler options #
####################
# setup include paths
INCLUDES = \
	-I$(PRINTF_SOURCE_DIR) \
	-I$(COMMON_SOURCE_DIR) \
	-I$(DRIVER_SOURCE_DIR) \
	-I$(PROGRAM_SOURCE_DIR)

# setup flags (may be pre-set before including this file)
CFLAGS  += -O2 -g -Wall $(INCLUDES) $(RISCV_GCC_OPTS)
ASFLAGS += 
LDFLAGS += -L. -T $(SW_ROOT)/common/link.ld $(RISCV_GCC_OPTS)
LIBS    += -lm -lc -lgcc

###########
# Targets #
###########
# convert all sources to objects
PRINTF_OBJ  = $(PRINTF_SRC:.c=.o)
PORT_OBJ    = $(PORT_SRC:.c=.o) $(PORT_ASM:.S=.o)
DRIVER_OBJ  = $(DRIVER_SRC:.c=.o)
PROGRAM_OBJ = $(PROGRAM_SRC:.c=.o) $(PROGRAM_ASM:.S=.o)
OBJS        = $(PRINTF_OBJ) $(PORT_OBJ) $(DRIVER_OBJ) $(PROGRAM_OBJ)

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
	$(CC) -c $(CFLAGS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(OUTFILES)
