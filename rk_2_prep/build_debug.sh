#!/bin/bash
gcc -c main.c -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -ggdb
gcc -c bin_file_car.c -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -ggdb
gcc -c struct_car.c -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -ggdb
gcc -o app.exe main.o bin_file_car.o  struct_car.o -lm