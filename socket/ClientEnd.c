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

#define RETURN_SUCCESS      EXIT_SUCCESS
#define RETURN_FAILURE      EXIT_FAILURE

int main()
{
    int ret_val = RETURN_FAILURE;
    int sockfd = 0;
    char *buffer = NULL;
    struct sockaddr_in sa_server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sockfd)
    {
        perror("call socket");
        return ret_val;
    }

    memset(&sa_server, 0, SOCK_ADDR_SIZE);
    sa_server.sin_family = AF_INET;
    sa_server.sin_port = htons(SERVICE_PORT);
    inet_pton(AF_INET, SERVICE_IP, &sa_server.sin_addr);

    ret_val = connect(sockfd, (struct sockaddr *)&sa_server, SOCK_ADDR_SIZE);
    if(0 > ret_val)
    {
        perror("call connect");
        return ret_val;
    }

    buffer = (char *)malloc(MAX_MSG_BUF_SIZE);
    if(NULL == buffer)
    {
        perror("call malloc");
        return ret_val;
    }

    recv(sockfd, buffer, MAX_MSG_BUF_SIZE, 0);
    printf("%s\n", buffer);

    ret_val = RETURN_SUCCESS;
    return ret_val;
}
