# Matrix math using Eigen
Eigen is a high performance header only C++ library. Instead of using ugly, complicated `c` routines from `arm` embedded library, it will be a huge relief to use familier `Eigen` multiplication.

This example tries to achieve it. There are some modifications that are required in the `makefile` and also in the familier `syscalls` too. The below lines will describe the changes required 

#### Note 
> Eigen is a header library, it has nothing to build and link. Just include the header files in  the project and you will be able to compile and use it.

```
# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -std=gnu++11 -fno-rtti -fno-exceptions
endif
```
Use `fno-exceptions` to reduce the size of compiled binary.

```
include $(CHIBIOS)/os/various/cpp_wrappers/chcpp.mk
```
Dont forget to include the `cpp` wrappers.

```
# LD   = $(TRGT)g++ 
LD   = $(TRGT)gcc
```

One more thing that I observed is that, if you link against the run time library support by un-commenting the line `LD   = $(TRGT)g++ `, the code size is going to drastically increase but it is required if we want to work with `stl` Standard Template Library in C++. I still have to figure out how we can use the STL.

```
UDEFS = -DCHPRINTF_USE_FLOAT=TRUE
```
This will enable float support in `chprintf`.

A great alternative to `STL` seems to be `ETL` Embedded Template Library. 
It is an opensource project which can be found at 
[ETL](https://github.com/ETLCPP/etl)