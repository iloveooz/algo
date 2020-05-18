@echo off
gxx -o rectree.exe *.cpp 
if errorlevel 1 goto noexec
rectree
:noexec
pause
