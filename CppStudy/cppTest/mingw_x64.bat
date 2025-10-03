@echo off
rem: rem:开头的一行是注释。
rem: @echo off表示命令不打印出来，直接执行。

mkdir build_mingw64
cd build_mingw64 
cmake -G "MinGW Makefiles" ..
mingw32-make
echo finished.
pause