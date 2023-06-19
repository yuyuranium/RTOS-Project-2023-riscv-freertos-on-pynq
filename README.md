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

## 

## Result

### Schematic Diagram

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/f5dedabd-8453-4b07-9d76-6f4a79b81a12)

### Synthesis and Implementation

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/1d4aca44-1970-4537-a5f9-85f7a549d9ab)

## Build Hardware Platform with FuseSoC

### Steps

- Install [fusesoc](https://github.com/olofk/fusesoc)
  
  ```
  $ pip3 install fusesoc==2.1
  ```

- Install git libraries
  
  ```
  $ cd pynq_z2/pl
  $ fusesoc library add --sync-type git ibex https://github.com/lowRISC/ibex.git                            # ibex library
  $ fusesoc library add --sync-type git pulp-axi https://github.com/pulp-platform/axi.git                   # pulp-axi library
  $ fusesoc library add --sync-type git pulp-common-cells https://github.com/pulp-platform/common_cells.git # pulp-common-cells library
  $ fusesoc library add --sync-type local ibex-axi .                                                        # ibex-axi local library
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

### Output

You will get a bitstream file and a hardware handoff file inside the build directory.

```
build/caslab_rtos_ibex_axi_1.0.0/default-vivado/caslab_rtos_ibex_axi_1.0.0.bit
build/caslab_rtos_ibex_axi_1.0.0/default-vivado/caslab_rtos_ibex_axi_1.0.0.hwh
```

## Build Software

You can use GNU make to build the software.

```
$ make -C sw/Barebone-Hello
```

Or for FreeRTOS applications

```
$ make -C sw/FreeRTOS-Demo-Hello
```

### Porting new program to the system

1. Make a directory in `sw`

2. Write your program and main function

3. Write a `Makefile` and define your program name
   
   ```
   PROGRAM := <YOUR_PROGRAM_NAME>
   ```
   
   **Note:** The program name must be the same as the directory name you created

4. Include the Makefile under `common` directory
   
   1. If you are writing a baremetal program
      
      ```
      include ../common/barebone.mk
      ```
   
   2. If you are using FreeRTOS
      
      ```
      include ../common/freertos.mk
      ```

## Boot Flow

1. Generate the bitstream (`*.bit`) and hardware handoff (`*.hwh`)

2. Copy the bitstrem and hardware handoff to the PS of PYNQ-Z2

3. Compile the software and get the binary file (`*.bin`)

4. Copy the binary file to the PS of PYNQ-Z2

5. Run the cell of in the [python notebook](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/blob/feat/update-readme/pynq_z2/ps/ibex_ctrl.ipynb) in PS to reset Ibex and boot

![image](https://github.com/yuyuranium/RTOS-Project-2023-riscv-freertos-on-pynq/assets/79467307/d1153f7b-bce9-45f2-a33d-0f00dec12c5a)
