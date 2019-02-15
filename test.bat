clang-cl test_main.c
clang-cl /LD test_dll.c test_main.lib
.\test_main

@echo off
del test_dll.dll
del test_dll.exp
del test_dll.lib

del test_main.exe
del test_main.exp
del test_main.lib
@echo on