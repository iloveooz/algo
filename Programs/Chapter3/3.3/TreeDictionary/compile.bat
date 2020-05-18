@echo off
gxx -Wno-deprecated -o treedictionary.exe *.cpp
if errorlevel 1 goto noexec
treedictionary
:noexec
pause
