@echo off
gxx -o intset.exe *.cpp
if errorlevel 1 goto noexec
intset
:noexec
pause
