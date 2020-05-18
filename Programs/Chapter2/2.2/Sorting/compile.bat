@echo off
gxx -o sorting.exe *.cpp
if errorlevel 1 goto noexec
sorting
:noexec
pause
