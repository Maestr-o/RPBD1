CC=g++
FLAGS=-Wall -Wextra -Werror
BUILD=../build/lab1.exe
LIBS=-lodbc32

all: build

build: main.o database.o
	@$(CC) $(FLAGS) main.o database.o -o $(BUILD) $(LIBS)

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp -o main.o

database.o: database.cpp
	@$(CC) $(FLAGS) -c database.cpp -o database.o

clean:
	@del *.o

rebuild:
	clean all