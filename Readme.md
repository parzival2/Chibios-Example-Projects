## Chibios Example Projects
This repository holds all the programs that I have tried when I am learning how to program Microcontroller boards using Chibios. Most of the programs work using `STM32F4-Discovery` board but they can also be ported to other boards, but just make sure that the pin assignments are correct. 
Here is a short explanation of all the folders in this repository along with their function.


| Folder name | Function |
|---|---|
| ArmMathExample | A Small program that will utilize Arm math libraries to compute matrix multiplication.|
| Blink_from_Thread | Example that will blink on board LEDs of STM32F4-Discovery board from Chibios threads |
| Blink_LED_PWM | Uses a PWM driver to blink on board LEDs |
| Breathing_LED_PWM| Uses PWM driver to simulate breathing pattern using on board LEDs. The brightness of LED will gradually increase and decrease.|
| LED_blink_GPT | Uses a General Purpose Timer to blink LEDs |
| PAL_Interrupt_Blink | Uses Interrupt to blink an on board LED |
| PIN_switch_GPT | Uses GPT to call a function periodically.|
| SerialPrint | Uses USART to print some ouput to terminal. |
| SPIExample | Uses SPI to determine whether the MPU9250 is connected to the board. It just reads `WHO_AM_I` register on the board. |
| MPU9259_C++ | The accelerometer and gyroscope values from the `MPU9250` is read and sent over `USB_CDC` connection. C++ is used in this project.|
| RosSerial_MPU9250 | Uses `rosserial` to send IMU data over `USB_CDC` connection.|
| BlackSTM32F4VET_LED_Blink | Uses Black STM32F4VET6 board and blinks its on board LEDs. The board definition files were also created. |


### Black STM32F4 port : What is working?
Here is a small over view of what is working on `Black STM32F4VET` board.


 - [x] Blink LEDs
 - [ ] USB communication
 - [ ] SPI
 - [ ] I2C
 - [ ] SD Card Reading and Writing


 Made using [stackedit](https://stackedit.io/app#)
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE5MjQ1NTMxNTVdfQ==
-->