#!/bin/bash
#Build the test and runs them

wd=$PWD

clear
echo Cleaning previous builds...
echo ---------------------------
rm build/*
echo
echo "Compiling... 
------------
     Flags: -Wall -Wextra -std=c++0x 
     Libraries: -lboost_unit_test_framework -lstdc++ 
     Includes: -I$wd/include/ -
               -I$wd/test/ 
     Sources: test/test_unit.cpp
     Build to: -o build/test_units" 
gcc -Wall -Wextra -std=c++0x -o build/test_units test/test_unit.cpp -lboost_unit_test_framework -lstdc++ -I$wd/include/ -I$wd/test/ 

echo
echo Executing Test
echo --------------
./build/test_units

read -n 1 -s
