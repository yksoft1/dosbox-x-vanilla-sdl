@echo off
cd sdl
nmake -f nmakefile clean
cd ..\zlib
nmake -f nmakefile clean
cd ..\libpng
nmake -f nmakefile clean
cd ..
