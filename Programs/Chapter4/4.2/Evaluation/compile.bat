@echo off
gxx -o evaluation.exe *.cpp
if errorlevel 1 goto noexec
evaluation
:noexec
pause
