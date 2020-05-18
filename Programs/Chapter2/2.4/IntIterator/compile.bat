@echo off
gxx -o intiterator.exe *.cpp
if errorlevel 1 goto noexec
intiterator
:noexec
pause
