install:
	g++ -std=c++11 src/matrix.cpp -o matrix.o -c
	g++ -std=c++11 m-l.cpp -o m-l.o -c
	g++ -std=c++11 matrix.o m-l.o -o m-l
