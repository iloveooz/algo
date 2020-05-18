@echo off
gxx -o skeleton.exe *.cpp
if errorlevel 1 goto noexec
skeleton
:noexec
pause
