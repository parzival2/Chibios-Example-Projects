# SPI Communication

A Simple SPI communication example that communicates with [GY91](https://artofcircuits.com/product/10dof-gy-91-4-in-1-mpu-9250-and-bmp280-multi-sensor-module), a 10DOF sensor containing [MPU9250](https://www.invensense.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf) and AK8964(https://www.akm.com/akm/en/file/datasheet/AK8963C.pdf). 

```C
static const SPIConfig spiConfig = {
		false,      % Whether using Circular Buffer mode
		NULL,       % Operation Callback
		GPIOB,      % Chip select line
		12,         % Chip select pin
		SPI_BaudRatePrescaler_8,      
		0
};
``` 
As with any driver, the config of the driver is important. Another important point with the SPI driver is the alternative pin configuration

```C
  palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New SCK.     */
  palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New MISO.    */
  palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New MOSI.    */
  palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL |
                             PAL_STM32_OSPEED_HIGHEST);       /* New CS.      */
  palSetPad(GPIOB, 12);
```
Alternative pin configurations can be found in STM32 manual. 

This example just reads `WHO_AM_I` register and if the MPU9250 is properly connected, it should reply with `0x71`. 