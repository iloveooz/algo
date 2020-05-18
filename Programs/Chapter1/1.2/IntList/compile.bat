@echo off
gxx -o intlist.exe *.cpp
if errorlevel 1 goto noexec
intlist
:noexec
pause
