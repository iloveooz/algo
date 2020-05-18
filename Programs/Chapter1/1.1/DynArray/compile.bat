@echo off
gxx -o dynarray.exe *.cpp
if errorlevel 1 goto noexec
dynarray
:noexec
pause
