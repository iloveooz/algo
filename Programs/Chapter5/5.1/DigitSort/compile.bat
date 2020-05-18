@echo off
gxx -Wno-deprecated -o digsort.exe *.cpp
if errorlevel 1 goto noexec
digsort
:noexec
pause
