CC=g++
FLAGS=-Wall -Wextra -Werror
BUILD=../build/lab1
LIBS=-lodbc

all: build

build: main.o database.o
	@$(CC) $(FLAGS) main.o database.o -o $(BUILD) $(LIBS)

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp -o main.o

database.o: database.cpp
	@$(CC) $(FLAGS) -c database.cpp -o database.o

clean:
	@rm -f *.o

rebuild:
	clean all