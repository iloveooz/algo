@echo off
gxx -o triedictionary.exe *.cpp
if errorlevel 1 goto noexec
triedictionary
:noexec
pause
