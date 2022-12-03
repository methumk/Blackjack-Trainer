CC = g++ -std=gnu++0x

MAIN_DEPS = main.cpp

all: main 

main:
	$(CC) $(MAIN_DEPS) -o bj.exe


clean:
	rm -rf bj.exe *.o