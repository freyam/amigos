CC = gcc
CFLAGS = -Wall -g

default:
	$(CC) $(CFLAGS) main.c interface.c amigos.c heap.c -o amigos && ./amigos

com:
	$(CC) $(CFLAGS) main.c interface.c amigos.c heap.c -o amigos

dbg:
	$(CC) $(CFLAGS) -g main.c interface.c amigos.c heap.c -o amigos
	gdb amigos

run:
	./amigos

test:
	$(CC) $(CFLAGS) lab.c -o lab && ./lab

clean:
	rm -rf amigos lab data/*

import:
	curl "https://api.mockaroo.com/api/5bf8e450?count=1000&key=47166f30" > "data/UserDatabase.csv"