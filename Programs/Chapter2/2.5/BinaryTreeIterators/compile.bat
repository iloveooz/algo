@echo off
gxx -o treeiterators.exe *.cpp 
if errorlevel 1 goto noexec
treeiterators
:noexec
pause
