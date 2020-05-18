@echo off
gxx -o expression.exe *.cpp
if errorlevel 1 goto noexec
expression
:noexec
pause
