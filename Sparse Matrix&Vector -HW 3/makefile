all: begin

begin: main.o
	g++ -std=c++11 main.o SparseVector.o SparseMatrix.o -o exe

main.o: main.cpp SparseVector.cpp SparseMatrix.cpp
	g++ -std=c++11 -c main.cpp SparseVector.cpp SparseMatrix.cpp

clean:
	rm *.o exe