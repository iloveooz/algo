@echo off
gxx -Wno-deprecated -o searchtree.exe *.cpp 
if errorlevel 1 goto noexec
searchtree
:noexec
pause
