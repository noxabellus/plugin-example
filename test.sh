#!/bin/sh

clang test_main.c -ldl -otest_main -Wl,--export-dynamic
clang -fPIC -shared test_dll.c -otest_dll.so
./test_main

rm test_dll.so
rm test_main