CC = gcc
CFLAGS = -Wall

default:
	$(CC) $(CFLAGS) main.c -o friendsbook && ./friendsbook

com:
	$(CC) $(CFLAGS) main.c -o friendsbook

run:
	./friendsbook

x:
	$(CC) $(CFLAGS) test.c -o test && ./test

clean:
	rm -rf friendsbook