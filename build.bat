

@echo off
cls
setlocal

set target=day06_2.cpp
set compile=-nologo -Fe:main.exe -I..\my_libs2 -Zi -O2 -wd4505 -D_CRT_SECURE_NO_WARNINGS -W3
set linker=-link /STACK:0x4000000,0x4000000

if not "%1"=="" set target=%1
cl %target% %compile% %linker%