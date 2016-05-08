CC=g++
CFLAGS=-std=c++11 -Wall -g
LFLAGS=-lboost_iostreams -lboost_system -lboost_filesystem

all:
	$(CC) $(CFLAGS) $(LFLAGS) main.cpp -o cachepp 
clean:
	rm *.o cachepp
