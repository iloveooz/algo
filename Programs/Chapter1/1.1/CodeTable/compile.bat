@echo off
gxx -o codetable.exe *.cpp
if errorlevel 1 goto noexec
codetable
:noexec
pause
