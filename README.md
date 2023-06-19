# RTOS-Project-2023-riscv-freertos-on-pynq

Porting FreeRTOS to a RISC-V based system on PYNQ-Z2

## Port Introduction

### Hardware

- **Board**: PYNQ-Z2

- **Processor**: [lowRISC Ibex RISC-V core](https://github.com/lowRISC/ibex) on [Zynq 7000 SoC](https://www.xilinx.com/products/silicon-devices/soc/zynq-7000.html)

### Compiler

- [lowRISC GCC toolchain](https://github.com/lowRISC/lowrisc-toolchains) targeting Ibex

## System Architecture

The hardware platform is built on ZYNQ FPGA

### PS side

- Dual-core ARM Coretex-A9 running Linux (for debugging)

### PL side

- Ibex: Soft-core RISC-V CPU

- System AXI Bus

- BRAM (on-chip SRAM)

- UART, GPIO and Timer

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/90f93d9e-dacb-4372-a015-3781cbefbcb3)

## Boot Flow

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/d1153f7b-bce9-45f2-a33d-0f00dec12c5a)

## Result

### Schematic Diagram

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/f5dedabd-8453-4b07-9d76-6f4a79b81a12)

### Synthesis and Implementation

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/1d4aca44-1970-4537-a5f9-85f7a549d9ab)

## Build Vivado Project with fusesoc

### Steps

- Install fusesoc
  
  ```
  $ pip3 install fusesoc==2.1
  ```
- Install git libraries
  
  ```
  $ fusesoc library add --sync-type git ibex https://github.com/lowRISC/ibex.git                            # ibex library
  $ fusesoc library add --sync-type git pulp-axi https://github.com/pulp-platform/axi.git                   # pulp-axi library
  $ fusesoc library add --sync-type git pulp-common-cells https://github.com/pulp-platform/common_cells.git # pulp-common-cells library
  $ fusesoc library add --sync-type local ibex-axi [relate path to pynq/pl]                                 # ibex-axi local library
  ```
- Install ibex dependencies 
  
  ```
  $ cd fusesoc_libraries/ibex
  $ pip3 install -r python-requirements.txt
  ```
- Build and run vivado Project
  
  ```
  $ bash scripts/build_proj.sh
  ```
