all: datTest

datTest: dataStructure.cpp dataStructure.h Entity.cpp Entity.h pluginTypes.h datTestTypes.cpp datTestTypes.h datTest.cpp
	g++ -Wall -std=c++1y Entity.cpp dataStructure.cpp datTest.cpp datTestTypes.cpp -o datTest

clean:
	rm datTest
