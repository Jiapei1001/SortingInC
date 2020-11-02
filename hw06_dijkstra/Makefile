compile: a6.h a6.c hashtable.c
	gcc -g a6.c -o a6

run: compile
	./a6

memcheck:
	valgrind --leak-check=full ./a6

clean:
	rm ./a6