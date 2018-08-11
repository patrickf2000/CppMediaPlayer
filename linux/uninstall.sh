#!/bin/bash
echo "Uninstalling..."

rm /usr/local/bin/CppMediaPlayer
rm /usr/share/applications/cpp-media-player.desktop

update-desktop-database

echo "Done" 
