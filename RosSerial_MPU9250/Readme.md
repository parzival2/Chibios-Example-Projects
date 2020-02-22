# Communicating with ROS-Serial
Ros serial can be used to communicate with ros from microcontrollers. This is an attempt to communicate with Ros using Ros-serial on STM32.

All the messages contained in Ros are headers, we first have to generate headers. The headers required can be generated using

```
rosrun rosserial_client make_libraries .
```
#### Note
> The `.` at the end is indicating that the headers be generated in the same folder where we opened up the terminal.

## Working with ros-serial
ROS serial is designed to run on Microcontrollers and it can run on any processor that has serial port and C++ support. For ros serial to work, the hard has to be connected to ros serial. It has to know how to access serial port, the time passed since the start etc.

The above step can be achieved by providing an interface between the hardware and rosserial.

```cpp
class Hardware
{

  Hardware();

  // any initialization code necessary to use the serial port
  void init(); 

  // read a byte from the serial port. -1 = failure
  int read()

  // write data to the connection to ROS
  void write(uint8_t* data, int length);

  // returns milliseconds since start of program
  unsigned long time();

};
```
[reference for the above code](http://library.isr.ist.utl.pt/docs/roswiki/rosserial_client(2f)Tutorials(2f)Adding(20)Support(20)for(20)New(20)Hardware.html)

## Essential files
There are some essential files required inorder to make the whole ros-communcation work.
1. syscalls - Located in extras
2. Modification for syscalls_cpp.cpp in chibios.

```c
#include <stdio.h>
#include <errno.h>

#include "osal.h"

#include "syscalls_cpp.hpp"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((used))
void _exit(int status){
   (void) status;
   osalSysHalt("Unrealized");
   while(TRUE){}
}

__attribute__((used))
pid_t _getpid(void){
   return 1;
}

#undef errno
extern int errno;
__attribute__((used))
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

__attribute__((used))
void _open_r(void){
  return;
}

void __cxa_pure_virtual() {
  osalSysHalt("Pure virtual function call.");
}

#ifdef __cplusplus
}
#endif
```

If you compare it with the original, you can see that we have added `__attribute__((used))` for every function. This tells the compiler that the static variable should be retained in the object file, even if it is unreferenced. Even with `Os` and `O0` there are some errors like

```
/usr/lib/gcc/arm-none-eabi/4.8/../../../arm-none-eabi/lib/armv6-m/libg.a(lib_a-abort.o): In function `abort':
/build/buildd/newlib-2.1.0+git20140818.1a8323b/build/arm-none-eabi/armv6-m/newlib/libc/stdlib/../../../../../../newlib/libc/stdlib/abort.c:63: undefined reference to `_exit'
/usr/lib/gcc/arm-none-eabi/4.8/../../../arm-none-eabi/lib/armv6-m/libg.a(lib_a-signalr.o): In function `_kill_r':
/build/buildd/newlib-2.1.0+git20140818.1a8323b/build/arm-none-eabi/armv6-m/newlib/libc/reent/../../../../../../newlib/libc/reent/signalr.c:61: undefined reference to `_kill'
/usr/lib/gcc/arm-none-eabi/4.8/../../../arm-none-eabi/lib/armv6-m/libg.a(lib_a-signalr.o): In function `_getpid_r':
/build/buildd/newlib-2.1.0+git20140818.1a8323b/build/arm-none-eabi/armv6-m/newlib/libc/reent/../../../../../../newlib/libc/reent/signalr.c:96: undefined reference to `_getpid'
```

After burning the generated executable, the data can easily be seen using

```bash
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM1
```

The values from the ros_serial can be visualized using 
```bash
rosrun plotjuggler PlotJuggler
```
and subscribing to the interested topic. This example publishes Accelerometer and Gyroscope values as `sensor_msgs/imu` on `imu` topic.

[Plotting Example](https://mega.nz/#!9ddzRQzY!Ov6qh_NjWt8fsZr6m6i7I3HuyRDGA7P-2cvdt5xrpuo)

## Interesting links about rosserial
[Protocol](http://library.isr.ist.utl.pt/docs/roswiki/rosserial(2f)Overview(2f)Protocol.html)