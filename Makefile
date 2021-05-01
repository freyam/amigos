CC = gcc
CFLAGS = -Wall

default:
	$(CC) $(CFLAGS) main.c friendsbook.c interface.c minheap.c -o friendsbook && ./friendsbook

com:
	$(CC) $(CFLAGS) main.c friendsbook.c interface.c minheap.c -o friendsbook

run:
	./friendsbook

test:
	$(CC) $(CFLAGS) lab.c -o lab && ./lab

clean:
	rm -rf friendsbook lab