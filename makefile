CC = g++
CFLAGS = -Wall -g
.DEFAULT_GOAL := naitive
naitive: main.o plate.o utils.o
	$(CC) $(CFLAGS) -o sourceplate_script src/main.o src/plate.o src/utils.o
main.o: src/main.cpp src/plate.h src/utils.h
	$(CC) $(CFLAGS) -c src/main.cpp -o src/main.o

plate.o: src/plate.h
	$(CC) $(CFLAGS) -c src/plate.cpp -o src/plate.o


utils.o: src/utils.h src/plate.h
	$(CC) $(CFLAGS) -c src/utils.cpp -o src/utils.o

.PHONY: clean
clean:
	@rm -f src/*.o
