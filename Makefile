confiables: confiables.o
	g++ -o confiables confiables.o

confiables.o: confiables.cpp
	g++  -c confiables.cpp -std=c++11


