#ifndef _REQUESTS_
#define _REQUESTS_
#include <string>
#include <vector>
using namespace std;

char *compute_get_request(char *host, char *url, char *url_params, char *praji, char *auth);
char *compute_post_request(char *host, char *url, char *form_data, char *praji, char *contType, char *auth);

#endif