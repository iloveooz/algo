@echo off
gxx -o dictionary.exe *.cpp
if errorlevel 1 goto noexec
dictionary
:noexec
pause
