@echo off
if not exist build mkdir ..\build
pushd build

del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp

set warnings_to_ignore=-wd4201 -wd4204 -wd4255 -wd4668 -wd4820 -wd4100 -wd4189 -wd4711 -wd4710 -wd4101 -wd4296 -wd4311 -wd4115 -wd4702 -wd4456 -wd4555

REM Asset Cooker Build
REM cl -nologo -O2 -Zi -FC -WX -Wall %warnings_to_ignore% ..\code\cooker.c /link user32.lib gdi32.lib -incremental:no -opt:ref
REM Game Build

REM Define lib path.
set "sdl2=C:\Libs\SDL2\SDL2-2.0.14"
set "sdl2_image=C:\Libs\SDL2\SDL2_image-2.0.5"
set "sdl2_ttf=C:\Libs\SDL2\SDL2_ttf-2.0.15"
set "env=x64"

if not exist SDL2.dll robocopy %sdl2%\lib\%env% . *.dll /NFL /NDL /NJH /NJS /nc /ns /np
if not exist SDL2_image.dll robocopy %sdl2_image%\lib\%env% . *.dll  /NFL /NDL /NJH /NJS /nc /ns /np
if not exist SDL2_ttf.dll robocopy %sdl2_ttf%\lib\%env% . *.dll  /NFL /NDL /NJH /NJS /nc /ns /np

cl /Fegame.exe -nologo -O2 -FC %warnings_to_ignore%^
     ..\source\sdl_main.cpp /I %sdl2%\include /I %sdl2_image%\include /I %sdl2_ttf%\include^
    /link %sdl2%\lib\%env%\SDL2.lib %sdl2%\lib\%env%\SDL2main.lib %sdl2_image%\lib\%env%\SDL2_image.lib %sdl2_ttf%\lib\%env%\SDL2_ttf.lib^
    shell32.lib -incremental:no -opt:ref /SUBSYSTEM:CONSOLE

del lock.tmp
del *.obj

popd

REM Compiler Flags:

REM Zi  : debug info (Z7 older debug format for complex builds)
REM Zo  : More debug info for optimized builds
REM FC  : Full path on errors
REM Oi  : Always do intrinsics with you can
REM Od  : No optimizations
REM O2  : Full optimizations
REM MT  : Use the c static lib instead of searching for dll at run-time
REM MTd : Sabe as MT but using the debug version of CRT
REM GR- : Turn off C++ run-time type info
REM Gm- : Turn off incremental build
REM EHa-: Turn off exception handling
REM WX  : Treat warning as errors
REM W4  : Set Warning level to 4 (Wall to all levels)
REM wd  : Ignore warning
REM fp:fast    : Ignores the rules in some cases to optimize fp operations
REM Fmfile.map : Outputs a map file (mapping of the functions on the exr)

REM Linker Options:

REM subsystem:windows,5.1 : Make exe compatible with Windows XP (only works on x86)
REM opt:ref               : Don't put unused things in the exe
REM incremental:no        : Don't need to do incremental builds
REM LD                    : Build a dll
REM PDB:file.pdb          : Change the .pdb's path
