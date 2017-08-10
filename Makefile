help:
	#Please see the readme for how to compile this project

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

firstTimeLXL:
	sudo apt install libreadline-dev libsfml-dev git

firstTimeLXW: firstTimeLXL
	echo "Installing MinGW Cross-Compiler"
	sudo apt install g++-mingw-w64-x86-64
	echo "Downloading and setting up SFML with MinGW"
	sudo apt install unzip
	mkdir -p Build/
	wget -O Build/source.zip "https://www.sfml-dev.org/files/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit.zip"
	unzip Build/source.zip -d Build/
	#Move files to the right places
	sudo cp -r Build/SFML-2.4.2/lib/ /usr/x86_64-w64-mingw32/
	sudo cp -r Build/SFML-2.4.2/include/ /usr/x86_64-w64-mingw32/include
	#Give files the right permissions
	sudo find /usr/x86_64-w64-mingw32/lib/ -type d -exec chmod 755 {} \;
	sudo find /usr/x86_64-w64-mingw32/lib/ -type f -exec chmod 655 {} \;
	sudo find /usr/x86_64-w64-mingw32/include/ -type d -exec chmod 755 {} \;
	sudo find /usr/x86_64-w64-mingw32/include/ -type f -exec chmod 655 {} \;
	echo "Getting Thread Library"
	wget -O Compiler/mingw.thread.h "https://raw.githubusercontent.com/meganz/mingw-std-threads/master/mingw.thread.h"
	echo "Cleaning up"
	rm -r Build/

#To be run on a Mac, the first time trying to compile an EMA program
firstTimeMXM:
	echo "Installing Brew, and using brew to install dependancies"
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	brew install sfml
	brew install readline
	brew install gcc
	brew install wget
	echo "Downloading SFML"
	mkdir -p Build/
	wget -O Build/source.tar.gz "https://www.sfml-dev.org/files/SFML-2.4.2-osx-clang.tar.gz"
	gunzip Build/source.tar.gz
	#Move files to the right places
	sudo cp -r Build/SFML-2.4.2/lib/ /usr/local/Cellar/gcc/7.1.0/lib/gcc/7/
	sudo cp -r Build/SFML-2.4.2/include/ /usr/local/Cellar/gcc/7.1.0/include/c++/7.1.0/
	#Give files the right permissions
	sudo find /usr/local/Cellar/gcc/7.1.0/ -type d -exec chmod 755 {} \;
	sudo find /usr/local/Cellar/gcc/7.1.0/ -type f -exec chmod 655 {} \;
	echo "Cleaning up"
	rm -r Build/

#
#
#

#To be run on Linux, to comple for Linux
LXL: Compiler/Compiler.cpp configureLXL
	g++ -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#To be run on Linux, to compile for Windows
LXW: Compiler/Compiler.cpp configureLXW
	g++ -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#To be run on a Mac, to compile for a Mac
MXM: Compiler/Compiler.cpp configureMXM
	/usr/local/bin/g++-7 -Wall -Wextra -pedantic -std=c++17 -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#
#
#

clean:
	rm compile

cleanAll:
	rm compile
	rm mainP*
