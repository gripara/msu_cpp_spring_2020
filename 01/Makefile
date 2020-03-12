CC = g++ -std=c++1y

all: test

test: main.o allocator.o
	$(CC) -o test main.o allocator.o
 
main.o: main.cpp allocator.h
	$(CC) -c main.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) -c allocator.cpp
clean:
	rm -rf *.o test
