# RTOS-Project-2023-riscv-freertos-on-pynq

Porting FreeRTOS to a RISC-V based system on PYNQ-Z2

## Port Introduction

### Hardware

- **Board**: PYNQ-Z2

- **Processor**: [lowRISC Ibex RISC-V core]([GitHub - lowRISC/ibex: Ibex is a small 32 bit RISC-V CPU core, previously known as zero-riscy.](https://github.com/lowRISC/ibex)) on [XC7Z020]([Zynq 7000 SoC](https://www.xilinx.com/products/silicon-devices/soc/zynq-7000.html))

### Compiler

- [lowRISC GCC toolchain]([GitHub - lowRISC/lowrisc-toolchains: UNSUPPORTED INTERNAL toolchain builds](https://github.com/lowRISC/lowrisc-toolchains)) targeting Ibex

## System Architecture

The hardware platform is built on ZYNQ FPGA

### PS side

- Dual-core ARM Coretex-A9 running Linux (for debugging)

### PL side

- Ibex: Soft-core RISC-V CPU

- System AXI Bus

- BRAM (on-chip SRAM)

- UART, GPIO and Timer

![](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_46159778b6f2b83e0e26bb165563f434.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1687160454&Signature=BBNIiAxBSHTD3EhHBGTCfk9mLdg%3D)

## Boot Flow

![](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_c4c8b0c79a869e2f1a383782cc83a266.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1687160531&Signature=jq7blNw9K4KMv3EIZ3ixQ924f6w%3D)

## Result

### Schematic Diagram

![](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_9349c80322221b86964f075f69197312.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1687160689&Signature=IpvILqnepvlw7K9kypzcTMMF3Ak%3D)

### Synthesis and Implementation

![](https://hackmd-prod-images.s3-ap-northeast-1.amazonaws.com/uploads/upload_1b11332bdaafd764261550f37ee27954.png?AWSAccessKeyId=AKIA3XSAAW6AWSKNINWO&Expires=1687160999&Signature=q%2FGLJL%2FaqrGg0ML3SHSe%2BarZxzw%3D)

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
