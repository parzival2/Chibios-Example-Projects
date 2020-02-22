# Driving LED using PWM signal

PWM(Pulse Width Modulation) is a famous technique to drive motors and lights. This is the technique that is used in dimming LEDs, changing
the speed of DC Motor etc. In ChibiOS like every driver PWM driver has to be started before using it. The driver can be started using `pwmStart()` function and supplying one of the four PWM drivers `(PWMD1, PWMD2, PWMD3, PWMD4)`. The driver can be customized using `PWMConfig()` struct which contains important information about the driver. 

Lets elucidate with an example : 
```C
static PWMConfig pwmCFG =
{
   1000000,              /* 100kHz PWM clock frequency */
   10,                   /* PWM period */
   NULL,                 /* No callback */
   /*
    * Enable all channels
    */
   {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
   },
   0,
   0
};
```
The arguments in the above code snippet can be easily understood from the comments situated beside every line of the code. After the PWM
driver has been started, individual channel can be started using `pwmEnableChannel()` function by suppling one of the used PWMDriver and the channel number(0-3) and the `width` of the pulse.

## Calculation of Width in pwmEnableChannel()
Considering the above defined config as an example, if we want the output PWM frequency to be 10000(10kHz) and duty cycle of 10percent i.e. the 
output will be high 10percent of the time, then the width that should be supplied to `pwmEnableChannel()` will be

dutyCycle 	= 	pwmEnableChannel_Width / PWM period(in config)

PWMFrequency 	= 	ClockFrequency(1st argument in config) / PWM period


