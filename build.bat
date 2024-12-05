

@echo off
cls
setlocal

set target=day05_1.cpp
set compile=-nologo -Fe:main.exe -I..\my_libs2 -Zi -Od
set linker=-link /STACK:0x4000000,0x4000000

if not "%1"=="" set target=%1
cl %target% %compile% %linker%