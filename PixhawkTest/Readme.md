## Pixhawk Test
This program simply blinks the Amber-LED on [Pixhawk2.4.8](https://ardupilot.org/copter/docs/common-pixhawk-overview.html) board. It is important to note that the board is not programmed via ST-Link debugger interface but using the USB port as the controller board already has a boot loader interface and accessing the debug pins is a bit of [hassle](https://ardupilot.org/dev/docs/debugging-with-gdb-on-stm32.html). This is just a demonstration to prove that, that board can also be programmed as well and I was planning to use the same board for more complicated projects like [pixhawk-ekf](https://github.com/parzival2/pixhawk_ekf), where a custom implementation of EKF will be implemented for learning. 
## Flashing
The files for flashing has been copied from Ardupilot project 
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTk4NTYyODI4OCwtMTg2NjcxNTc4Nl19
-->