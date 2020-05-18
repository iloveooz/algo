@echo off
gxx -o listdictionary.exe *.cpp
if errorlevel 1 goto noexec
listdictionary
:noexec
pause
