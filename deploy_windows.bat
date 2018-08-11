@echo off

cd build
mkdir winbin

copy src\CppMediaPlayer.exe .\winbin
copy C:\Unix\bin\libsettings.dll .\winbin

cd winbin
windeployqt --release --compiler-runtime CppMediaPlayer.exe

cd ..