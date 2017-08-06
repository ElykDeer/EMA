all:

#Set up defines for compiling on linux for windows
configureLXW:
	echo "#define LINUX_X_WINDOWS 1" > Compiler/Compiler.def

#Set up defines for compiling on linux for windows
configureLXL:
	echo "#define LINUX_X_LINUX 1" > Compiler/Compiler.def

#Set up defines for compiling on linux for windows
configureMXM:
	echo "#define MAC_X_MAC 1" > Compiler/Compiler.def

#This is outdated, was intended for the "Linux for Windows" subsystem, but
#  SFML would be using and linking Linux graphics things and that doesn't work on Windows
#Compile: Compiler/Compiler.cpp
#	g++-7.1 -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

LinuxFirstTime:
	sudo apt install libreadline-dev libsfml-dev git
LinuxForWindowsFirstTime:
	echo "Installing MinGW Corss-Compiler and cmake"
	sudo apt install g++-mingw-w64-x86-64 cmake-qt-gui
	echo "Cloning SFML into ../SFML"
	cd ../
	git clone https://github.com/SFML/SFML
	echo "Installing SFML Dependancies"
	sudo apt install freetype jpeg x11 xrandr xcb x11-xcb xcb-randr xcb-image opengl flac ogg vorbis vorbisenc vorbisfile openal pthread
	cmake-gui

#To be run on a Mac, the first time trying to compile an EMA program
macFirstTime:
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	brew install sfml
	brew install readline
	brew install gcc

#
#
#

#To be run on Linux, to comple for Linux
linux: Compiler/Compiler.cpp
	g++ -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#To be run on Linux, to compile for Windows
windows: Compiler/Compiler.cpp
	x86_64-w64-mingw32-g++ -I/usr/include/ -Wall -Wextra -pedantic -std=c++17 Main/main.cpp Main/dataStructure/dataStructure.cpp Main/Entity.cpp Main/ThreadManager.cpp Main/Graphics/Graphics.cpp Plugins/datTest/datTestTypes.cpp -o mainP.exe -pthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -ljpeg -lwinmm -lgdi32

#To be run on a Mac, to compile for a Mac
mac: Compiler/Compiler.cpp
	/usr/local/bin/g++-7 -Wall -Wextra -pedantic -std=c++17 -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#
#
#

clean:
	rm compile

cleanAll:
	rm compile
	rm mainP
