# Protocoale de comunicatii:
# Tema2
# Makefile

# Tema initial era in C, dar am modificat cand 
# am primit confirmare ca putem utiliza STL

CFLAGS = -Wall -g -std=c++11 -lm

# Portul pe care asculta serverul (de completat)
PORT = 1234

# Adresa IP a serverului (de completat)
IP_SERVER = 127.0.0.1

all: server client

# Compileaza server.c
server: server.c
	g++ ${CFLAGS}  server.c  -o server

# Compileaza client.c
subscriber: subscriber.c
	g++ ${CFLAGS} subscriber.c -o subscriber.

.PHONY: clean run_server run_client

# Ruleaza serverul
run_server:
	./server ${PORT}

# Ruleaza clientul
run_client:
	./subscriber 12344 ${IP_SERVER} ${PORT}

clean:
	rm -f server subscriber
