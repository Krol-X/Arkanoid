@echo off

cd ..\Release
del *.ini
del *.lib
del game.exe
..\installer\upx.exe Arkanoid.exe
..\installer\7zr.exe a archive.7z *.* -mx5 -mf=BCJ2
copy /b ..\installer\7zS2.sfx + ..\installer\config.txt + archive.7z game.exe
rem ..\installer\upx.exe game.exe
del archive.7z