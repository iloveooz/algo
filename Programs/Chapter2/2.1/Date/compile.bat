@echo off
gxx -o dates.exe *.cpp 
if errorlevel 1 goto noexec
dates
:noexec
pause
