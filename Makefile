all: Compiler

Compiler: Compiler/Compiler.cpp
	g++-7.1 -Wall -Wextra -pedantic -std=c++1z Compiler/Compiler.cpp -o compiler -lstdc++fs

clean:
	rm compiler
