CC = gcc
CFLAGS = -g -Wall -lm

build: editor

editor:
	$(CC) -o editor editor.c commands.c $(CFLAGS)
test:
	rm -f editor
	rm -f *.out
	$(CC) -o editor editor.c commands.c $(CFLAGS)
	./editor
.PHONY:clean
clean:
	rm -f editor
	rm -f *.out
