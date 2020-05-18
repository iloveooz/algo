@echo off
gxx -o bilist.exe *.cpp
if errorlevel 1 goto noexec
bilist
:noexec
pause
