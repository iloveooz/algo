@echo off
gxx -o bmarkers.exe *.cpp
if errorlevel 1 goto noexec
bmarkers
:noexec
pause
