# dosbox-x-vanilla-sdl
A test fork of joncampbell123's DosBox-X (https://github.com/joncampbell123/dosbox-x/) that should be able to build with vanilla SDL1 and SDL2.

# Why this?
I always build DosBox-X from source code and use either MinGW+MSYS or mingw-w64 environment.
Some of other programs rely on features removed from DosBox-X's in-tree SDL to work best in some older PCs, and I'm bored to build the in-tree SDL everytime I build DosBox-X.
I'll try to cherry-pick most PC-98 related features from joncampbell123's as I mainly use DosBox-X as a PC-98 emulator.
