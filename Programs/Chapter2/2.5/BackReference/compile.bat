@echo off
gxx -o backrefiterator.exe *.cpp 
if errorlevel 1 goto noexec
backrefiterator
:noexec
pause
