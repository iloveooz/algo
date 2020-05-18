@echo off
gxx -o conversion.exe *.cpp
if errorlevel 1 goto noexec
conversion
:noexec
pause
