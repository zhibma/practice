#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_ADDR_SIZE      sizeof(struct sockaddr_in)
#define SERVICE_IP          "127.0.0.1"
#define SERVICE_PORT        50067
#define MAX_MSG_BUF_SIZE    2000

int main()
{
    int ret_val = 0;
    int sockfd = 0;
    char *buffer = NULL;
    struct sockaddr_in sa_server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sockfd)
    {
        perror("call socket");
        return 1;
    }

    memset(&sa_server, 0, SOCK_ADDR_SIZE);
    sa_server.sin_family = AF_INET;
    sa_server.sin_port = htons(SERVICE_PORT);
    sa_server.sin_addr.s_addr = inet_addr(SERVICE_IP);

    ret_val = connect(sockfd, (struct sockaddr *)&sa_server, SOCK_ADDR_SIZE);
    if(0 > ret_val)
    {
        perror("call connect");
        return 1;
    }

    buffer = (char *)malloc(MAX_MSG_BUF_SIZE);
    if(NULL == buffer)
    {
        perror("call malloc");
        return 1;
    }

    recv(sockfd, buffer, MAX_MSG_BUF_SIZE, 0);
    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}
