# Sending strings using SerialDriver in ChibiOS
The Serial driver is used to send strings or info using UART port of STM32F4. The default baud rate of the SerialDriver is 38400 and can be easily changed using the config struct of the SerialDriver.

## Requirements
Like every driver, the SerialDriver in ChibiOS needs to be started using `sdStart` command which takes the pointer to the driver object and the config struct that is used to modify parameters of the driver. 
Most useful information that I have found while searching about SerialDriver is http://www.playembedded.org/blog/stm32-usart-chibios-serial/. 
## Coding
### Config struct of SerialDriver
The config struct of the SerialDriver looks like the following
```C
static SerialConfig sd2Config = {
        115200,                     /* Baudrate */
        0,
        USART_CR2_STOP1_BITS,
        0
};
```
Where the first parameter is the baud rate and the other three parameters are CR1, CR2 and CR3 registers that are mentioned in the official ST document.
The strings and information can be printed using `chprintf` which can be used by including the `mk` file in the main Makefile of the project.
```C
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/boards/ST_STM32F4_DISCOVERY/board.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
include $(CHIBIOS)/os/hal/lib/streams/streams.mk
```
To use `chprintf` functionality the `chprintf.h` header file should be included.
```C
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
```
##Note
Before using the SerialDriver, the mode of the corresponding GPIO pins should be changed. In the example provided, the SD2 has been used corresponding to USART2 on the STM32F4 board and PA2 and PA3 pins can be used by changing their mode to AF7.