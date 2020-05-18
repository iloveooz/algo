@echo off
gxx -o calc.exe *.cpp
if errorlevel 1 goto noexec
calc
:noexec
pause
