all:

#This is outdated, was intended for the "Linux for Windows" subsystem, but
#  SFML would be using and linking Linux graphics things and that doesn't work on Windows
Compile: Compiler/Compiler.cpp
	g++-7.1 -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#To be run on Linux, to comple for Linux
linux: Compiler/Compiler.cpp
	g++ -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

#To be run on Linux, to compile for Windows
windows: Compiler/Compiler.cpp
	x86_64-w64-mingw32-gcc -I/usr/include/ -Wall -Wextra -pedantic -std=c++1y Main/main.cpp Main/dataStructure/dataStructure.cpp Main/Entity.cpp Main/ThreadManager.cpp Main/Graphics.cpp Plugins/datTest/datTestTypes.cpp -o mainP.exe -pthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -ljpeg -lwinmm -lgdi32

#To be run on a Mac, the first time trying to compile an EMA program
macFirstTime:
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	brew install sfml
	brew install readline
	brew install gcc

#To be run on a Mac, to compile for a Mac
mac: Compiler/Compiler.cpp
	/usr/local/bin/g++-7 -Wall -Wextra -pedantic -std=c++17 -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

clean:
	rm compile

cleanAll:
	rm compile
	rm mainP
