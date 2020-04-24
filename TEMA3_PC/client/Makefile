CC=g++
CFLAGS=-I.

client: client.c requests.c helpers.c parson.c
		$(CC) -std=c++11 -o client client.c requests.c helpers.c parson.c -Wall
		
run: client
		./client

clean:
		rm -f *.o client
