#!/bin/bash

gcc -Wall -s -I. -c -o strip.o strip.cpp
gcc -Wall -g -I. -c -o tripper.o tripper.cpp
g++ -L. -g -o tripper tripper.o -Xlinker --start-group ./strip.o -Xlinker --end-group
rm strip.o tripper.o