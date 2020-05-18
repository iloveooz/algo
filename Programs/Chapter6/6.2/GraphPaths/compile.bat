@echo off
gxx -o shortest.exe *.cpp
if errorlevel 1 goto noexec
shortest
:noexec
pause
