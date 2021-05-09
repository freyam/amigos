CC = gcc
CFLAGS = -Wall
FILES = main.c interface.c amigos.c heap.c avl.c queue.c


default:
	$(CC) $(CFLAGS) $(FILES) -o amigos
	./amigos

com:
	$(CC) $(CFLAGS) $(FILES) -o amigos

dbg:
	$(CC) $(CFLAGS) -g $(FILES) -o amigos
	gdb amigos

test:
	$(CC) $(CFLAGS) lab.c -o lab && ./lab

clean:
	rm -rf amigos lab graph/*

import:
	curl "https://api.mockaroo.com/api/5bf8e450?count=1000&key=47166f30" > "data/RandomUserDatabase.csv"