@echo off
gxx -o stacks.exe *.cpp 
if errorlevel 1 goto noexec
stacks
:noexec
pause
