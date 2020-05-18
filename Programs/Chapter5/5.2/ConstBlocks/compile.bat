@echo off
gxx -Wno-deprecated -o constblocks.exe *.cpp
if errorlevel 1 goto noexec
constblocks
:noexec
pause
