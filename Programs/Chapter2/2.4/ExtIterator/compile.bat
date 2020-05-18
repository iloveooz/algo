@echo off
gxx -o extiterator.exe *.cpp
if errorlevel 1 goto noexec
extiterator
:noexec
pause
