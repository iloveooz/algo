@echo off
gxx -o sets.exe *.cpp
if errorlevel 1 goto noexec
sets
:noexec
pause
