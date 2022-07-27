CC=gcc 
SRC=*.c 
LIB=-lpthread
EXE=emp	
build:
	$(CC) -g $(SRC) -o $(EXE) $(LIB)
run:
	./$(EXE)
clean:
	rm -f *.o *.i *.dat $(EXE)
lint:
	splint $(SRC)
check:
	valgrind --leak-check=yes ./$(EXE)
execute: clean build run
memcheck: clean build check