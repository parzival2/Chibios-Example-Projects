## Description

This program switches the on board pins to test whether the GPT is functioning
accurately using a logic analyzer.

The program starts by defining a Timer(GPT4) and a config that is required for 
the timer. The config contains all the callback that the timer will call 
when the timer is triggered. 

Lets start with an example : 

```C
static const GPTConfig gpt4cfg = {
  10000,    /* 10kHz timer clock.*/
  gpt4cb,   /* Timer callback.*/
  0,
  0
};
```

In the above code snippet we have defined a timer config with timer clock of 
10kHz and a timer callback which will be called periodically when ever we start
the timer.

The periodicity of the timer will be decided based on the value(number of ticks)
given to the function `gptStartContinuous()`.

Suppose we want to call the callback every 0.1 seconds(100milli seconds). The
value of the tick_count in `gptStartContinuous()` will be 1000. The value has
been calculated using

0.1 secs = x / 10000

x = 10000 * 0.1