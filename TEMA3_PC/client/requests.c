#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
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

using namespace std;

char *compute_get_request(char *host, char *url, char *url_params, char *praji, char *auth)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    /*
        PAS 1: Scriem numele metodei, calea, parametri din url (daca exista) si tipul protocolului
    */
    if (url_params != NULL)
    {
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else
    {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    /*
        PAS 2: Adaugam host-ul
    */

    // TODO Ex 0
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (auth != NULL)
    {
        sprintf(line, "Authorization: Bearer %s", auth);
        compute_message(message, line);
    }

    //COOKIE
    if (praji != NULL){
        sprintf(line, "Cookie: %s", praji);
        compute_message(message, line);
    }
    
    
    
    /*
        PAS 4: Adaugam linia de final
    */
    sprintf(line, "");
    compute_message(message, line);
    //TODO Ex 0
    return message;
}
char *compute_post_request(char *host, char *url, char *form_data, char *praji, char *contType, char *auth)
{

    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    /*
        PAS 1: Scriem numele metodei, calea si tipul protocolului
    */

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    /*
        PAS 2: Adaugam host-ul
    */

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (auth != NULL)
    {
        sprintf(line, "Authorization: Bearer %s", auth);
        compute_message(message, line);
    }

    if (praji != NULL)
    {
        sprintf(line, "Cookie: %s", praji);
        compute_message(message, line);
    }

    sprintf(line, "Content-Type: %s", contType);
    compute_message(message, line);

    sprintf(line, "Content-Length: %d", (int)strlen(form_data));
    compute_message(message, line);

    /*
        PAS 4: Adaugam linia de final de antent
    */

    sprintf(line, "");
    compute_message(message, line);

    /*
        PAS 5: Adaugam data
    */

    sprintf(line, "%s", form_data);
    compute_message(message, line);

    return message;
}