# RTOS-Project-2023-riscv-freertos-on-pynq
Porting FreeRTOS to a RISC-V based system on PYNQ-Z2

## Build Vivado Project with fusesoc
### Steps
- Install fusesoc
    ```
    $ pip3 install fusesoc==2.1
    ```
- Install git libraries
    ```
    $ fusesoc library add --sync-type git ibex https://github.com/lowRISC/ibex.git          # ibex library
    $ fusesoc library add --sync-type git pulp-axi https://github.com/pulp-platform/axi.git # pulp-axi library
    $ fusesoc library add --sync-type local ibex-axi [relate path to pynq/pl]               # ibex-axi local library
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
