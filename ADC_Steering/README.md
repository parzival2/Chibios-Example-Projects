## Events

In ChibiOS, [events](http://www.chibios.org/dokuwiki/doku.php?id=chibios:book:kernel_events) play a major role. Apart from [MessageBoxes](http://www.chibios.org/dokuwiki/doku.php?id=chibios:book:kernel_mailboxes) they are the main form of communication between threads. The events functionality in ChibiOS can be enabled setting `CH_CFG_USE_EVENTS` to true. 



#### Defining events

Events are defined using `event_source_t` and they should be initialized before by using `chEvtObjectInit` and supplying the pointer to the underlying event source. 

#### Defining event listeners

Event listeners are the objects that listen for a particular events. These would normally be `Threads` that are normally interested in particular events. They can be defined using `event_listener_t` and the thread that is interested in the events should register for a particular event using 

`chEvtRegisterMask(&ledEventSource, &ledEventListener, EVENT_MASK(0));` 

#### Defining flags

Flags can be like extra parameters that are passed to threads that are registered to receive events. They can be defined using `event_flags_t`. After defining everything, the thread can listen on events using `chEvtWaitAny` that waits on any event. 

This simple example listens on an event that blinks each `LED` on STM32F4 and the `LED` is decided using the flag.

```c++
chEvtWaitAny(EVENT_MASK(0));
flags = chEvtGetAndClearFlags(&ledEventListener);
if(flags == LED3)
{
    palToggleLine(LINE_LED3);
}
else if(flags == LED4)
{
    palToggleLine(LINE_LED4);
}
else if(flags == LED5)
{
    palToggleLine(LINE_LED5);
}
else if(flags == LED6)
{
    palToggleLine(LINE_LED6);
}
```