#CppMediaPlayer

###General info

This is yet another media player.
It is capable of playing most common video and music files.
For music, you can additionally run it in the background.

The entire program is written in C++ and only uses the Qt library.
Although it has not yet been tested, it should run on Windows as well.

###Building

A qmake .pro file is included. 
Although it can be used to build the program, it is primarily intended to be used for development in QtCreator.
To build with qmake, simply open a terminal in your current directory, and type 'qmake' and then 'make'.
You can also use QtCreator to build as well.

It is highly recommended to use cmake to build the program.
To do so, execute the following commands:   
`mkdir build`  
`cd build`  
`cmake ..`   
`make`   

###Installing

There are a couple of ways you can install.      

####The manual way   
Run these commands as root.   
`cp ./build/cpp-media-player /usr/local/bin`   
`cp ./cpp-media-player.desktop /usr/share/applications`   

####Using cmake
Refresh cmake:
`cmake ..`   
Run as root:
`make install`   

####The easy way
This is the easiest method as it allows you to make an installable debian package.   
A script is provided to build the package.
To use it, simply type:   
`./deb.sh`   
You may have to make it executable.
If so, type the following command:   
`chmod 777 ./deb.sh`

###Uninstalling   
There are two ways you can uninstall.

####The manual way   
Run these commands as root.   
`rm /usr/local/bin/cpp-media-player`   
`rm /usr/share/applications/cpp-media-player.desktop`   

####The easy way   
Note that this only works if you installed via the debian package.   
This is one command that should work:   
`apt-get remove cpp-media-player`

###Disclaimer
Use this program and any of the commands give above at your own risk.
I am not responsible if you mess something up.
If you do not feel comfortable running something, then don't!


