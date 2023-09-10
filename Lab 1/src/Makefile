CC=g++
FLAGS=-Wall -Wextra -Werror
BUILD=../build/rpbd1.exe

all: build

build: main.o
	@$(CC) $(FLAGS) main.o -o $(BUILD)

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp -o main.o

clean:
	del *.o

rebuild:
	clean all