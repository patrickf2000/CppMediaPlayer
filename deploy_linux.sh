#!/bin/bash
cd build
mkdir linux_bin

cp src/CppMediaPlayer linux_bin
cp ../share/cpp-media-player.desktop linux_bin
cp ../linux/* linux_bin
cp ../COPYING* linux_bin

if [ -f /usr/local/lib/libsettings.so ] ; then
	cp /usr/local/lib/libsettings.so linux_bin
elif [ -f /usr/lib/libsettings.so ] ; then
	cp /usr/lib/libsettings.so linux_bin
else
	echo "Error: Could not find libsettings."
	echo "Make sure the file is named libsettings.so and that it is in one of the paths listed below:"
	echo "* /usr/local/lib"
	echo "* /usr/lib"
	exit 1
fi 

tar -czvf CppMediaPlayer_bin_linux.tar.gz linux_bin/*
