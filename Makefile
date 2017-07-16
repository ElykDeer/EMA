all: Compile

Compile: Compiler/Compiler.cpp
	g++-7.1 -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compile -lstdc++fs -lreadline

clean:
	rm compile

cleanAll:
	rm compile
	rm mainP
