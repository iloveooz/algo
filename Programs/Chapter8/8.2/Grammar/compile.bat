@echo off
gxx -o grammar.exe *.cpp
if errorlevel 1 goto noexec
grammar
:noexec
pause
