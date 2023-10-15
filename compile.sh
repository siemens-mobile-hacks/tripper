#!/bin/bash
CC=g++
$CC -Wall -s -I. -c -o strip.o strip.cpp
$CC -Wall -g -I. -c -o tripper.o tripper.cpp
$CC -L. -g -o tripper tripper.o strip.o
rm strip.o tripper.o