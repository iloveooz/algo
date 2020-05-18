@echo off
gxx -o iterators.exe *.cpp
if errorlevel 1 goto noexec
iterators
:noexec
pause
