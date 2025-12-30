# DISCO LIGHTS PROJECT

### A STM32 NUCLEO-F767ZI board based music-synced LED light project.

## A Small Demo


## HARDWARE
### Parts Used:
- [nucleo-f767zi](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html)
- [Mic: SEN0526](https://wiki.dfrobot.com/SKU_SEN0526_Fermion_I2S_MEMS_Microphone)
- [LED Strips](https://www.digikey.com/en/products/detail/adafruit-industries-llc/3811/9092302)

### Pin Assignments
| Pin | Nucleo Pin |
|:---:|:---:
| Mic: 3V3 | 3V3
| Mic: GND | GND
| Mic: WS | PA4
| Mic: SCK | PA5
| Mic: DO | PA7
| LED: 5V | 5V
| LED: GND | GND
| LED | PE13

Check on board pin layout: [Here](https://os.mbed.com/platforms/ST-Nucleo-F767ZI/)

## SOFTWARE
### CODE STRUCTURE
- __main_p.c__
Main Entry point for program
- __Led.c__
Interacts with LED
- __mic.c__
Reads in data from mic
- __uart.c__
Used for debugging data
- __utils.c__
Some utility functions

### TOOLS
1. __SCRIPTS__
    - __record_uart.sh__
    Logs in data received from Serial COMM port into a file.
        - Usage: ./tools/bash/record_uart.sh [-p PORT] [-b BAUD] [-d DURATION] [-o OUTFILE]

2. __PYTHON__
    - __analyze.ipynb__
    Reads in the mic's logged data to play and plot it.

## GETTING STARTED

### Download STM32 CUBEMX
This allows us to initialize peripherals through a GUI Tool.
- Download: [Here](https://www.st.com/en/development-tools/stm32cubemx.html)

### Download STM32 Cube IDE Extension For VS Code
This allows us to edit, run and debug our code right from the VS Code
- Download: [Here](https://marketplace.visualstudio.com/items?itemName=stmicroelectronics.stm32-vscode-extension)

### Clone This Repository
```bash
git clone https://github.com/ayank674/disco-lights.git
```
