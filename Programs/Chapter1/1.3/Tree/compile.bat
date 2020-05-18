@echo off
gxx -o tree.exe *.cpp 
if errorlevel 1 goto noexec
tree
:noexec
pause
