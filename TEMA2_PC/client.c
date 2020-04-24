/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <list>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s id server_address server_port\n", file);
	exit(0);
}

int max(int a, int b)
{
	return (a < b) ? b : a;
}

int main(int argc, char *argv[])
{
	int sockfd, n, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];

	fd_set set;			// multimea de citire folosita in select()
	fd_set tmp_set; // multime folosita temporar
	int fdmax;

	
	FD_ZERO(&tmp_set);

	if (argc < 4)
	{
		usage(argv[0]);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[3]));
	ret = inet_aton(argv[2], &serv_addr.sin_addr); //scrie ip-ul in sock
	DIE(ret == 0, "inet_aton");

	ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //se conecteaza la serv
	DIE(ret < 0, "connect");
	//dupa connect, trimite id-ul

	sprintf(buffer, argv[1], strlen(argv[1]));
	n = send(sockfd, buffer, strlen(buffer), 0);
		

	
	while (1)
	{
		FD_ZERO(&set);
		FD_SET(sockfd, &set);
		FD_SET(0, &set);
		fdmax = max(0, sockfd);

		ret = select(fdmax + 1, &set, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		if (FD_ISSET(0, &set))
		{

			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN - 1, stdin);

			if (strncmp(buffer, "exit", 4) == 0)
			{
				break;
			}
			// se trimite mesaj la server
			n = send(sockfd, buffer, strlen(buffer), 0);
		}

		if (FD_ISSET(sockfd, &set))
		{
		  	n = recv(sockfd, buffer, sizeof(buffer), 0);
			DIE(n < 0, "recv");

			if (n == 0)
			{
				// conexiunea s-a inchis
				printf("Serverul a inchis conexiunea\n");
				break;
			}

			printf("%s\n", buffer);
			if (strncmp(buffer, "[REFUZAT]", 9) == 0)
			{
				return 0;
			}
		}
	}

	close(sockfd);

	return 0;
}
