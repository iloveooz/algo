@echo off
gxx -o strangestrings.exe *.cpp 
if errorlevel 1 goto noexec
strangestrings
:noexec
pause
