@echo off
setlocal
set "PATH=C:\msys64\mingw64\bin;%PATH%"
C:\msys64\mingw64\bin\g++.exe -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o exp2.exe
