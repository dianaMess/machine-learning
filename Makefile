install:
	g++ -std=c++11 src/matrix.cpp -o matrix.o -c
	g++ -std=c++11 regression.cpp -o regression.o -c
	g++ -std=c++11 matrix.o regression.o -o regression
