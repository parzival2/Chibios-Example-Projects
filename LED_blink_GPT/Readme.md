## Description

This program blinks the on board LEDs using the General Purpose Timer driver
in ChibiOS. This comment gives a detailed explanation of what is going on in
the program.
 
Explanation
----------
Initialize two GPT drivers one for each LED. Initialize each of them
with the clock timer having 100KhZ frequency as can be seen in configs of
the two drivers(gpt4cfg and gpt3cfg). The callback will be called when the
timers are run from the main thread.
 
The LED4 will be switched on and in the next step the timer GPT4 is called
Continuously with a delay of 100mseconds then the main thread sleeps for 5
seconds, then switches off LED4 then once again starts the timer GPT4. Inside
the GPT4 timer callback it will switch on and off LED5 with 100msec delay.

