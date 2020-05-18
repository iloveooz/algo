@echo off
gxx -o queens.exe *.cpp
if errorlevel 1 goto noexec
queens
:noexec
pause
