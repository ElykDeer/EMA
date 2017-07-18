all: Compile

Compile: Compiler/Compiler.cpp
	g++-7.1 -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

linux: Compiler/Compiler.cpp
	g++ -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

windows:
	x86_64-w64-mingw32-gcc -I/usr/include/ -Wall -Wextra -pedantic -std=c++1y Main/main.cpp Main/dataStructure/dataStructure.cpp Main/Entity.cpp Main/ThreadManager.cpp Main/Graphics.cpp Plugins/datTest/datTestTypes.cpp -o mainP.exe -pthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -ljpeg -lwinmm -lgdi32

clean:
	rm compile

cleanAll:
	rm compile
	rm mainP
