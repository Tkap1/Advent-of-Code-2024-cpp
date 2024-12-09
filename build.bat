

@echo off
cls
setlocal

del *.ilk 2> NUL
del *.obj 2> NUL
del *.pdb 2> NUL

set target=day09_2.cpp
set compile=-nologo -Fe:main.exe -I..\my_libs2 -Zi -Od -wd4505 -D_CRT_SECURE_NO_WARNINGS -W3
set linker=-link /STACK:0x4000000,0x4000000 -INCREMENTAL:NO

if not "%1"=="" set target=%1
cl %target% %compile% %linker%