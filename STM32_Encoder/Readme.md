# Breathing LED

You might have seen in so many circuits that the led looks like it is breathing. It can be done by chaning the PWM frequency in a loop. 
Since ChibiOS has a PWM driver, we will be using it to drive the LED. Note that I have tried to change the PWM frequency dynamically in 
a callback, but it doesn't work and the program crashes(i guess).

In the config for PWM driver, we can define a callback which will be called everytime the PWM pulse is triggered. 

```C
static PWMConfig pwmCFG =
{
   100000,                   /* 10kHz PWM clock frequency */
   1000,                   /* PWM period = ticks / PWM clock frequency */
   pwmCallback,                    /* No callback */
   /*
    * Enable all channels
    */
   {
    {PWM_OUTPUT_ACTIVE_HIGH, pwmChannel1Callback},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
   },
   0,
   0
};
``` 
As can be seen in the above code snippet, each channel can have its own callback and the total PWM driver can have its own callback. 
The callbacks will only be called when they are enabled using `pwmEnablePeriodicNotification()` for PWMDriver and `pwmEnableChannelNotification()` for individual channel.

The PWM Frequency of individual channel can be modified in the loop using pwmEnableChannel(), as far as I understood, this can not be changed
or called from callbacks. This must be done in the thread that the PWM driver has been started in.
