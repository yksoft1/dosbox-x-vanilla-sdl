@echo off
cd sdl
nmake -f nmakefile
cd ..\zlib
nmake -f nmakefile
cd ..\libpng
nmake -f nmakefile
cd ..
