#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <string>
#include <vector>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

using namespace std;

#define IP_srv "185.118.200.35"

void get_ip(char *name, char *ip)
{
    struct addrinfo hints, *res;
    char buffer[BUFLEN];

    memset(&hints, 0, sizeof(hints));

    hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
    hints.ai_family = AF_UNSPEC;
   
    getaddrinfo(name, NULL, &hints, &res);
    
    if (res->ai_family == AF_INET)
    {
     struct sockaddr_in *in = (struct sockaddr_in *)res->ai_addr;
     inet_ntop(res->ai_family, &(in->sin_addr), buffer, BUFLEN);
    }
    else if (res->ai_family == AF_INET6)
    {
         struct sockaddr_in6 *in = (struct sockaddr_in6 *)res->ai_addr;
         inet_ntop(res->ai_family, &(in->sin6_addr), buffer, BUFLEN);
    }

    sprintf(ip, "%s", buffer);
    freeaddrinfo(res);
}

void parse_json_only(char *response, std::string &data)
{
    char *pch = strtok(response, "\n;");
    while (pch != NULL)
    {
        pch = strtok(NULL, "\n;");
        if (pch[0] == '{')
        {
            data =(std::string)pch;
            break;
        }
    }
}

void parse_data(char *response, std::vector<std::string> &cookies, std::string &data)
{   
    char *pch = strtok(response, "\n;");
    while (pch != NULL)
    {
        pch = strtok(NULL, "\n;");
        if ( pch[0] == 'S'){
            char *temp = pch + 12;
            cookies.push_back((string)temp);
        }
        if (pch[0] == '{')
        {
            data = "[" + (std::string)pch + "]";
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    //int i;
    char *message;
    char *response = (char *)calloc(BUFLEN, sizeof(char));
    char *urlparams = (char *)calloc(BUFLEN, sizeof(char));
    char *token = (char *)calloc(BUFLEN, sizeof(char));
    std::string dat2parse;
    std::string data2send;
    char *praji = (char *)calloc(BUFLEN,sizeof(char));
    int sockfd;
    std::vector<std::string> cookies;
    std::vector<std::string> decoy;

    JSON_Value *root;
    JSON_Array *campuri;
    JSON_Object *obiect;
    JSON_Object *dat;
    
    //TODO etapa 0
    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection((char *)IP_srv, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_get_request)
    message = compute_get_request((char *)IP_srv, (char *)"/task1/start", NULL, NULL, NULL);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    parse_data(response, cookies, dat2parse);
    root = json_parse_string(dat2parse.c_str());
    campuri = json_value_get_array(root);
    obiect = json_array_get_object(campuri, 0);
    dat = json_object_dotget_object(obiect, "data");
        // printf("%s\n%s\n%s\n",
        //        json_object_get_string(obiect, "method"),
        //        json_object_dotget_string(obiect, "data.username"),
        //        json_object_dotget_string(obiect, "data.password"));
     printf("\n---------------------------------------------------\n\n");
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    
    data2send = (string)json_object_get_name(dat, 0) + "=" +
                (string)json_object_dotget_string(obiect, "data.username") +
                "&" + json_object_get_name(dat, 1) + "=" +
                json_object_dotget_string(obiect, "data.password");
    sprintf(praji, "%s; %s", cookies[0].c_str(), cookies[1].c_str());
    cookies.clear();

    // TASK 2
    
    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection((char *)IP_srv, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_post_request)
    message = compute_post_request((char *)IP_srv, (char *)json_object_get_string(obiect, "url"), (char *)data2send.c_str(), praji, (char *)json_object_get_string(obiect, "type"), NULL);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("%s", response);
    parse_data(response, cookies, dat2parse);
    root = json_parse_string(dat2parse.c_str());
    campuri = json_value_get_array(root);
    obiect = json_array_get_object(campuri, 0);
    dat = json_object_dotget_object(obiect, "data");
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    
    sprintf(praji, "%s; %s", cookies[0].c_str(), cookies[1].c_str());
    cookies.clear();
    sprintf(urlparams, "raspuns1=omul&raspuns2=numele&id=%s", json_object_dotget_string(obiect, "data.queryParams.id"));
    sprintf(token, "%s", json_object_dotget_string(obiect, "data.token"));

    // TASK 3
    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection((char *)IP_srv, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_post_request)
    message = compute_get_request((char *)IP_srv, (char *)json_object_get_string(obiect, "url"), urlparams, praji, token);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("%s", response);
    parse_data(response, cookies, dat2parse);
    root = json_parse_string(dat2parse.c_str());
    campuri = json_value_get_array(root);
    obiect = json_array_get_object(campuri, 0);
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    printf("\n---------------------------------------------------\n\n");

    sprintf(praji, "%s; %s", cookies[0].c_str(), cookies[1].c_str());
    cookies.clear();

    // TASK 4
    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection((char *)IP_srv, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_post_request)
    message = compute_get_request((char *)IP_srv, (char *)json_object_get_string(obiect, "url"), NULL, praji, token);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("%s", response);
    parse_data(response, cookies, dat2parse);
    root = json_parse_string(dat2parse.c_str());
    campuri = json_value_get_array(root);
    obiect = json_array_get_object(campuri, 0);
    dat = json_object_dotget_object(obiect, "data.queryParams");
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    printf("\n---------------------------------------------------\n\n");

    sprintf(praji, "%s; %s", cookies[0].c_str(), cookies[1].c_str());
    cookies.clear();

    // TASK 5 - GET WEATHER
    char *host = (char *)calloc(BUFLEN, sizeof(char));
    sprintf(host, "%s", json_object_dotget_string(obiect, "data.url"));
    char *p = strchr(host, '/');
    *p = 0;
    char *ip = (char *)calloc(BUFLEN, sizeof(char));
    get_ip(host, ip);
    char *url = (char *)calloc(BUFLEN, sizeof(char));
    sprintf(url, "%s", json_object_dotget_string(obiect, "data.url"));
    p = strchr(url, '/');
    printf("%s\n%s\n%s\n", ip, host, p);

    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection(ip, 80, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_post_request)
    sprintf(urlparams, "%s=%s&%s=%s",
            json_object_get_name(dat, 0),
            json_object_dotget_string(obiect, "data.queryParams.q"),
                json_object_get_name(dat, 1),
            json_object_dotget_string(obiect, "data.queryParams.APPID"));
    message = compute_get_request(host, p, urlparams, NULL, NULL);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("%s", response);
    parse_json_only(response, dat2parse);
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    printf("\n---------------------------------------------------\n\n");

    // TASK 5
    //Pas 1: Se deschide conexiunea (open_connection)
    sockfd = open_connection((char *)IP_srv, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    //Pas 2: Se creaza mesajul de request (compute_post_request)
    message = compute_post_request((char *)IP_srv, (char *)json_object_get_string(obiect, "url"), (char *)dat2parse.c_str(), praji, (char *)json_object_get_string(obiect, "type"), token);
    printf("%s", message);
    printf("\n---------------------------------------------------\n\n");
    //Pas 3: Se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);
    //Pas 4: Se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    //Pas 5: Se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    free(response);
    free(message);
    free(praji);
    free(token);
    free(urlparams);
    return 0;
}