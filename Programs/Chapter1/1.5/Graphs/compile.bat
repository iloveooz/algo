@echo off
gxx -o graphs.exe *.cpp
if errorlevel 1 goto noexec
graphs
:noexec
pause
