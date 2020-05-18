@echo off
gxx -o queues.exe *.cpp
if errorlevel 1 goto noexec
queues
:noexec
pause
