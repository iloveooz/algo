@echo off
gxx -o workers.exe *.cpp
if errorlevel 1 goto noexec
workers
:noexec
pause
