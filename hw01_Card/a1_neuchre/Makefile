all: play test

test: neuchre.h neuchre.c neuchre_test.c neuchre_helpers.c deck.c
	gcc neuchre.c deck.c neuchre_helpers.c neuchre_test.c -o test -g

play: neuchre.h neuchre.c neuchre_run.c deck.c neuchre_helpers.c
	gcc neuchre.c deck.c neuchre_helpers.c neuchre_run.c -o play -g

run_test: test
	./test

run_play: play
	./play

.PHONY: clean
clean:
	rm -f play
	rm -f test
