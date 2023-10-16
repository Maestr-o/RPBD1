CC=g++
FLAGS=-Wall -Wextra
BUILD=../build/prog.exe
LIBS=-lodbc32

all: build

build: main.o
	@$(CC) $(FLAGS) main.o -o $(BUILD) $(LIBS)

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp -o main.o

clean:
	@del *.o

rebuild:
	clean all