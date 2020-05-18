@echo off
gxx -o dynbackref.exe *.cpp 
if errorlevel 1 goto noexec
dynbackref
:noexec
pause
