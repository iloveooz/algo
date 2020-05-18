@echo off
gxx -o figures.exe *.cpp
if errorlevel 1 goto noexec
figures
:noexec
pause
