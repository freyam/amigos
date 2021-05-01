CC = gcc
CFLAGS = -Wall

default:
	$(CC) $(CFLAGS) main.c amigos.c interface.c minheap.c -o amigos && ./amigos

com:
	$(CC) $(CFLAGS) main.c amigos.c interface.c minheap.c -o amigos

run:
	./amigos

test:
	$(CC) $(CFLAGS) lab.c -o lab && ./lab

clean:
	rm -rf amigos lab