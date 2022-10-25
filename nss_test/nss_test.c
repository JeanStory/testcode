#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <nss.h>

#include <netdb.h>

extern enum nss_status
_nss_test_gethostbyname_r (const char *name, struct hostent *result,
                            char *buffer, size_t buflen, int *errnop,
                            int *herrnop);

enum nss_status
_nss_test_gethostbyname_r (const char *name, struct hostent *result,
			    char *buffer, size_t buflen, int *errnop,
			    int *herrnop)
{
    char cmd[256] = {0};
    snprintf(cmd, 256, "echo %s >> /home/test.txt", name);
    system(cmd);

    return NSS_STATUS_NOTFOUND;
}
