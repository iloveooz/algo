@echo off
gxx -o heap.exe *.cpp 
if errorlevel 1 goto noexec
heap
:noexec
pause
