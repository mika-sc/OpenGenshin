rem requires Turbo C installed at C:\TC
cd src
tcc -G -O2 -Ie:\tc\include -ml -c lt_sys.c lt_key.c lt_gfx.c lt_spr.c lt_sound.c genshin.c 
del *.LIB
tlib lt_lib.lib +lt_sys.obj+lt_key.obj+lt_gfx.obj+lt_spr.obj+lt_sound.obj
tlink c0l.obj genshin.obj lt_lib.lib,genshin.exe,, cl -Le:\tc\lib
@echo off
copy genshin.exe ..
del *.OBJ
del *.MAP
del genshin.exe
cd..
@echo on
