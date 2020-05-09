## Chibios ETL

A small experiment where the [ETL(Embedded template library)](https://www.etlcpp.com/) is used instead of STL as it wants Dynamic memory allocation. This is a simple program that passes the elements of a vector using mailbox from chibios. 

Main thread will modify the values and the worker thread will read it and print it to the terminal. Don't forget to include `etl_profile.h` header file.