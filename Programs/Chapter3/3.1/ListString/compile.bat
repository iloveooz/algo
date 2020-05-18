@echo off
gxx -o liststrings.exe *.cpp
if errorlevel 1 goto noexec
liststrings
:noexec
pause
