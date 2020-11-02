all: run

compile: chained_ht.h chained_ht.c anagrams_run.c
	gcc chained_ht.c anagrams_run.c -o anagrams_run

run: compile
	./anagrams_run

compile_test: chained_ht.h chained_ht.c anagrams_test.c
	gcc chained_ht.c anagrams_test.c -o anagrams_test

test: compile_test
	./anagrams_test
