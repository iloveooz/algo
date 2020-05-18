@echo off
gxx -Wno-warnings -o stacks.exe *.cpp
if errorlevel 1 goto noexec
stacks
:noexec
pause
