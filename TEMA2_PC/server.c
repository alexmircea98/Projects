#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "helpers.h"

using namespace std;

typedef struct
{
	int sok;
	string id;
	int SF;
	vector<string> msgStorage;
	//de implementat cu UDP acuma

} subscriber;

typedef struct
{
	string name;
	vector<subscriber> abonati; 

} topic;

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, sockudp, newsockfd, portno;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, ret;
	socklen_t clilen;

	fd_set read_fds; // multimea de citire folosita in select()
	fd_set tmp_fds;  // multime folosita temporar
	int fdmax;		 // valoare maxima fd din multimea read_fds

	if (argc < 2)
	{
		usage(argv[0]);
	}

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockudp = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sockudp < 0, "socket UDP");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket TCP");
	
	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	
	memset((char *)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockudp, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));

	ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(sockfd, &read_fds); // TCP
	FD_SET(sockudp, &read_fds); // TCP
	fdmax = max(sockudp, sockfd);

	vector<topic> topics;
	vector<subscriber> cliTCP;

	while (1)
	{
		tmp_fds = read_fds;
		FD_SET(0, &tmp_fds);
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		if (FD_ISSET(0, &tmp_fds))
		{

			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN - 1, stdin);

			if (strncmp(buffer, "exit", 4) == 0)
			{
				for ( i = 0; i <= fdmax; i++){
					close(i);
					FD_CLR(i, &read_fds);
				}
				printf("Deconectare clienti...\nExit");
				break;
			} else {
				printf("[Err] Doar comanda de exit acceptata");
			}
			// se trimite mesaj la server
			memset(buffer, 0, BUFLEN);
		}

		for (i = 1; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &tmp_fds) && (i != sockudp))
			{
				if (i == sockfd)
				{	
					// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
					// pe care serverul o accepta
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
					DIE(newsockfd < 0, "accept");

					//dupa acc primeste id si verifica daca exista
					memset(buffer, 0, BUFLEN);
					n = recv(newsockfd, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");
					
					bool unic = true;
					for (subscriber sub : cliTCP)
					{
						if (sub.id.compare(string(buffer)) == 0)
						{
							printf("[REFUZAT]ID %s deja exista!\n", buffer);
							sprintf(buffer, "[REFUZAT]ID client deja exista!");
							n = send(newsockfd, buffer, sizeof(buffer), 0);
							DIE(n < 0, "refuz conect");
							unic = false;
							break;
						}
					}

					if (unic)
					{
						//daca e ok, adauga id si socket
						subscriber temp;
						temp.sok = newsockfd;
						temp.id = std::string(buffer);
						cliTCP.push_back(temp);

						// se adauga noul socket intors de accept() la multimea descriptorilor de citire
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax)
						{
							fdmax = newsockfd;
						}

						printf("Noua conexiune de la %s, port %d, socket client %d cu id %s \n",
						inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd, cliTCP.back().id.c_str());
						sprintf(buffer, "[ACCEPTAT]Conexiune reusita");
						n = send(newsockfd, buffer, sizeof(buffer), 0);
						DIE(n < 0, "trimitere confirmare");
						memset(buffer, 0, BUFLEN);

						//later edit pentru trimitere mesaje la client reconectat
						for (topic topicul : topics){ //in topicuri
							for( subscriber abonatRevenit : topicul.abonati){ // in abonatii topicului
								if (abonatRevenit.id.compare(temp.id) == 0 && abonatRevenit.SF == 1){ //daca il gaseste
									//printf("GASIT!!! si are size %d \n", (int)abonatRevenit.msgStorage.size());
									for(string buffedmsg : abonatRevenit.msgStorage){ //trimite tot ce are
										memset(buffer, 0, BUFLEN);
										sprintf(buffer, "%s", buffedmsg.c_str());
										n = send(temp.sok, buffer, sizeof(buffer), 0);
										DIE(n < 0, "trimitere confirmare");
										memset(buffer, 0, BUFLEN);
										printf("trimit mesaj memorat");
									}
								}
							}
						}
					}
				}
				else
				{
					// s-au primit date pe unul din socketii de client,
					// asa ca serverul trebuie sa le receptioneze
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");

					if (n == 0)
					{
						// conexiunea s-a inchis
						
						close(i);
						//se scoate din clienti conectati
						for (int er=0; er < (int)cliTCP.size(); er++){
							if(cliTCP[er].sok == i){
								printf("Socket-ul client %d cu id %s a inchis conexiunea\n",
									 i, cliTCP[er].id.c_str());
								cliTCP.erase(cliTCP.begin() + er);
								break;
							}
						}
						
							// se scoate din multimea de citire socketul inchis
							FD_CLR(i, &read_fds);
					}
					else
					{
						printf("S-a primit de la clientul de pe socketul %d mesajul: %s\n", i, buffer);
						char *pch = strtok(buffer, " ");
						if (strcmp(buffer, "subscribe") == 0)
						{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{ //verifica topicul
							bool exists = false;
							int top;
							for (top = 0; top < (int)topics.size(); top++)
							{
								if (topics[top].name.compare(pch) == 0)
								{
									exists = true;
									break;
								}
							}
							if (exists)
							{ //daca exista
								for (subscriber s : cliTCP)
								{ //cauta clientul si il adauga in lista de abonati a topicului
									if (s.sok == i)
									{
										topics[top].abonati.push_back(s);
										break;
									}
								}
								pch = strtok(NULL, " ");
								if (pch != NULL)
								{ // daca SF exista
									topics[top].abonati.back().SF = atoi(pch);
								} else {
									sprintf(buffer, "[Err] Nu ai pus SF 0/1");
									n = send(newsockfd, buffer, sizeof(buffer), 0);
									DIE(n < 0, "Topicul nu exista inca");
									memset(buffer, 0, BUFLEN);
								}
							}
							else
							{ //daca nu exista
								sprintf(buffer, "[Err] Topicul nu exista inca / comanda greesita");
								n = send(newsockfd, buffer, sizeof(buffer), 0);
								DIE(n < 0, "Topicul nu exista inca");
								memset(buffer, 0, BUFLEN);
							}
						}
						else
						{
							sprintf(buffer, "[Err] Comanda gresita | nu ai pus niciun topic");
							n = send(newsockfd, buffer, sizeof(buffer), 0);
							DIE(n < 0, "trimitere Comanda gresita");
							memset(buffer, 0, BUFLEN);
						}
						}
						else if (strcmp(buffer, "unsubscribe") == 0)
						{
							pch = strtok(NULL, " ");
							if (pch != NULL)
							{ //verifica topicul
								bool exists = false;
								int top;
								for (top = 0; top < (int)topics.size(); top++)
								{
									if (topics[top].name.compare(pch) == 0)
									{
										exists = true;
										break;
									}
								}
								if (exists)
								{ //daca exista
									bool success = false;
									for (int k = 0; k < (int)topics[top].abonati.size(); k++)
									{ //cauta clientul si verifica daca este in lista de abonati a topicului
										if (topics[top].abonati[k].sok == i)
										{
											topics[top].abonati.erase(topics[top].abonati.begin() + k);
											success = true;
											break;
										}
									}
									if (success)
									{
										sprintf(buffer, "Ati fost dezabonat cu succes de la topicul %s", topics[top].name.c_str());
										n = send(newsockfd, buffer, sizeof(buffer), 0);
										DIE(n < 0, "trimitere confirmare");
										memset(buffer, 0, BUFLEN);
									}
									else
									{
										sprintf(buffer, "Nu erati abonat la topicul %s", topics[top].name.c_str());
										n = send(newsockfd, buffer, sizeof(buffer), 0);
										DIE(n < 0, "trimitere confirmare");
										memset(buffer, 0, BUFLEN);
									}
								}
								else
								{ //daca nu exista
									sprintf(buffer, "[Err] Topicul nu exista / daca esti sigur ca erai abonat, nu uita ca dupa numele topicului mai trebuie sa pui un (space)");
									n = send(newsockfd, buffer, sizeof(buffer), 0);
									DIE(n < 0, "trimitere confirmare");
									memset(buffer, 0, BUFLEN);
								}
							}
							else
							{
								sprintf(buffer, "[Err] Comanda gresita | nu sti spus niciun topic");
								n = send(newsockfd, buffer, sizeof(buffer), 0);
								DIE(n < 0, "trimitere confirmare");
								memset(buffer, 0, BUFLEN);
							}
						}
						else 
						{
							sprintf(buffer, "[Err] comanda nerecunoscuta / gresita");
							n = send(newsockfd, buffer, sizeof(buffer), 0);
							DIE(n < 0, "comanda necunoscuta");
							memset(buffer, 0, BUFLEN);
						}
								
					}
					

					DIE(n < 0, "send");
				}

				//-----------------------------------------------------------------------//

				
			}
			
		}
		if (FD_ISSET(sockudp, &tmp_fds)){
			//a venit mesaj pe udp
			clilen = sizeof(cli_addr);
			char mesaj_udp[6054], top[51], *mesg, ctet; // dimensiune in bytes 50 + 1*4 + 1500 *4
			int r = recvfrom(sockudp, mesaj_udp, 6054, 0, (struct sockaddr *)&cli_addr, &clilen);
			DIE(r < 0, "eroare primire mesaj udp");
			
			strncpy(top, mesaj_udp, 50);
			string messageToSend = (string)inet_ntoa(cli_addr.sin_addr) + ":" + to_string(ntohs(cli_addr.sin_port)) + " - " + top;
			printf("%s", messageToSend.c_str());
			bool topic_exists = false;
			int topicCurent;
			for(topicCurent = 0; topicCurent < (int)topics.size(); topicCurent++){
				if(topics[topicCurent].name.compare((string)top) == 0){
					topic_exists = true;
					break;
				}
			}

			if (topic_exists){

				mesg = mesaj_udp + 50;
				ctet = mesg[0];
				mesg = mesg + 1;
				char semn = mesg[0];
				char type[11], putere;
				
				uint32_t nr1;
				uint16_t nr2;
				char int32[4];
				char int16[2];
				switch ((int)ctet)
				{
				case 0: //e int
					sprintf(type, "INT");
					mesg = mesg + 1;
					memcpy(int32, mesg, 4);
					nr1 = (int32[0] << 0) | (int32[1] << 8) | (int32[2] << 16) | (int32[3] << 24);
					nr1 = ntohl(nr1);
					if ((int)semn)
					{
						sprintf(mesg, "-%d", nr1);
					} 
					else
					{
						sprintf(mesg, "%d", nr1);
					}
					// printf(" numar: %u\n", nr);
					break;

				case 1:
					sprintf(type, "SHORT_REAL");
					mesg = mesg + 1;
					memcpy(int16, mesg, 2);
					nr2 = (int16[1] << 0) | (int16[0] << 8);
					nr2 = ntohl(nr2);
					if ((int)semn)
					{
						sprintf(mesg, "-%u", nr2);
					}
					else
					{
						sprintf(mesg, "%u", nr2);
					}

					break;
				case 2:
					sprintf(type, "FLOAT");
					mesg = mesg + 1;
					memcpy(int32, mesg, 4);
					putere = mesg[5];
					//printf(" putere = %d ", putere);
					nr1 = (int32[0] << 0) | (int32[1] << 8) | (int32[2] << 16) | (int32[3] << 24);
					nr1 = ntohl(nr1);
					if ((int)semn)
					{
						sprintf(mesg, "-%2.1f", (float)nr1 * pow(10, (int)putere));
					}
					else
					{
						sprintf(mesg, "%2.1f", (float)nr1 * pow(10, (int)putere));
					}
					break;
				case 3:
					sprintf(type, "STRING");
					//e string deja, nu fac nimic
					break;
				default:
					break;
				}
				messageToSend += " - " + (string)type + " - " + (string)mesg;
				printf(" - %s -", type);
				printf(" %s\n", mesg);
				memset(mesaj_udp, 0, 6054);

				// dupa ce va merge formatarea cum trebuie

				//TODO: trimite mesajul tuturor
				for (subscriber sub : topics[topicCurent].abonati){
					//daca mai exista
					bool incaOn = false;
					for(subscriber client : cliTCP){
						if (sub.id.compare(client.id) == 0 ){
							incaOn = true;
							break;
						}
					}

					if(incaOn){
						sprintf(buffer, "%s", messageToSend.c_str());
						n = send(sub.sok, buffer, sizeof(buffer), 0);
						DIE(n < 0, "trimitere confirmare");
						memset(buffer, 0, BUFLEN);
					} else if (sub.SF == 1) {
						sub.msgStorage.push_back(messageToSend);
					}
					
				}
			} 
			else
			{ //create topic
				topic temp;
				temp.name = (string)top;
				topics.push_back(temp);
				printf("\n");
			}
				}
	}

	close(sockfd);
	close(sockudp);

	return 0;
}
