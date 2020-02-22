# Blinking LED from thread
The name ChibiOS itself defines that it is an operating system though for small memory footprint processors. Even though it is suitable for small foot print processors, it is fully capable of spawning threads and maintaining them. 

A Thread in ChibiOS can be started using the definition, where we define the name of the thread and its working area along with its priority. Threads are started with normal priority `NORMALPRIO` unless stated otherwise. 

The priority of the thread can be increased using small additions eg. `NORMALPRIO + 1`. If a thread has been set with this priority, it will have more priority than the thread that was started with `NORMALPRIO`.


```C
static THD_WORKING_AREA(ld4ledblink, 128);
static THD_FUNCTION(ld4LedThread, arg){
	(void)arg;
	/* Set thread name */
	chRegSetThreadName("ld4LedThread");
	/* Thread should not return, so begin a while loop */
	while(TRUE)
	{
		palTogglePad(GPIOD, GPIOD_LED4);
		chThdSleepMilliseconds(100);
	}
}
```
The above code snippet serves as a small example that explains how to define a thread in ChibiOS. The defined thread can be started using 

```C
chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink), NORMALPRIO+1, ld4LedThread, NULL);
```