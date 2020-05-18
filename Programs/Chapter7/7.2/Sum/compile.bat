@echo off
gxx -o sum.exe *.cpp
if errorlevel 1 goto noexec
sum
:noexec
pause
