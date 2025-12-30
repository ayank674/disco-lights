# DISCO LIGHTS PROJECT

### A STM32 NUCLEO-F767ZI board based music-synced LED light project.

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

## TODO
- ~~Your MOM~~ 😝
- Create a DSP (Digital Signal Processing) alogrithm to detect beats/ manipulate brightness of LED based on the input sound.
    - Analyze the tools/python/analyze.ipynb python notebook to get started with the kind of data we get.
    - Either create a Python script or C Program and use some of the logged music samples from logs/ to return brightness in __real time__.
    - Don't try too hard on the algorithm as we need it to be reasonably efficient to run on a small MCU chip.
    - If possible, you can do tempo detection as well to get a pace of the music and try to adjust the color according to it.
    - __References you can begin with__:
        - [Beat Detection](https://www.reddit.com/r/DSP/comments/1g5zrz2/realtime_beat_detection/)
        - [BPM Detection](https://www.reddit.com/r/DSP/comments/jjowj1/realtime_bpm_detection/)
        - [Real Time Beat Detection Blog](https://dev.to/hacker_ea/real-time-beat-detection-in-web-based-dj-applications-40p3)
        - [Tempo Classifier](https://youtu.be/yMbewdnupwU?si=-fFnKUJjP4iFMO2q)
        - [Tempo Sync 101](https://youtu.be/MFJI4j9uusc?si=qpt38_XPU_6r_K3u)
        - Any other cool sources you find :)
