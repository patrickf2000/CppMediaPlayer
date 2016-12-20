#!/bin/bash

if [ ! -d ./build ] ; then
    echo "The program does not seem to have been built."
    echo "To build, see the README file."
    exit 1
fi

echo "Building..."

mkdir -p ./build/deb/DEBIAN
mkdir -p ./build/deb/usr/share/applications
mkdir -p ./build/deb/usr/local/bin

cp ./control ./build/deb/DEBIAN
cp ./cpp-media-player.desktop ./build/deb/usr/share/applications
cp ./build/cpp-media-player ./build/deb/usr/local/bin

fakeroot dpkg-deb --build ./build/deb
mv ./build/deb.deb cpp-media-player.deb

echo "Done"
