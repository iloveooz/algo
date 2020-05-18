@echo off
gxx -o bintwins.exe *.cpp
if errorlevel 1 goto noexec
bintwins
:noexec
pause
