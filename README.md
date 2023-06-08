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
    $ fusesoc library add --sync-type git ibex https://github.com/lowRISC/ibex.git`          # ibex library
    $ fusesoc library add --sync-type git pulp-axi https://github.com/pulp-platform/axi.git` # pulp-axi library
    $ fusesoc library add --sync-type local ibex-axi [relate path to pynq/pl]`               # ibex-axi local library
    ```
- Install ibex dependencies 
    ```
    $ cd fusesoc_libraries/ibex
    $ pip3 install -r python-requirements.txt
    ```
- Run and build Vivado project
    ```
    $ fusesoc run caslab:rtos:ibex_axi:1.0.0 --pnr none --jobs [JOBS]
    ```
    The Vivado project should be located at `build/caslab:rtos:ibex_axi:1.0.0/default-vivado`
- Open project with Vivado
    ```
    $ vivado caslab:rtos:ibex_axi:1.0.0.xpr
    ```
