#!/bin/bash
echo "Installing..."

install CppMediaPlayer /usr/local/bin
install libsettings.so /usr/local/lib
install cpp-media-player.desktop /usr/share/applications

update-desktop-database
ldconfig

echo "Done" 
