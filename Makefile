all: datTest

datTest: datTest.cpp dataStructure.cpp dataStructure.h datTestTypes.cpp datTestTypes.h Entity.cpp Entity.h
	clear; g++ -Wall -std=c++1y datTest.cpp datTestTypes.cpp Entity.cpp dataStructure.cpp -o datTest
