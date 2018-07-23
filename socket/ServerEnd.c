#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_ADDR_SIZE      sizeof(struct sockaddr_in)
#define SERVICE_PORT        50067
#define MAX_QUENE_LEN       10
#define MAX_MSG_BUF_SIZE    2000

int service_handle(const int sock);

int main()
{
    int ret_val = 0;
    int sock_listen = 0;
    int sock_connect = 0;
    struct sockaddr_in sa_listen;

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sock_listen)
    {
        perror("call socket");
        return 1;
    }

    memset(&sa_listen, 0, SOCK_ADDR_SIZE);
    sa_listen.sin_family = AF_INET;
    sa_listen.sin_port = htons(SERVICE_PORT);
    sa_listen.sin_addr.s_addr = htonl(INADDR_ANY);

    ret_val = bind(sock_listen, (struct sockaddr *)&sa_listen, SOCK_ADDR_SIZE);
    if(0 > ret_val)
    {
        perror("call bind");
        return 1;
    }

    listen(sock_listen, MAX_QUENE_LEN);
    printf("Start listening...\n");

    while(1)
    {
        sock_connect = accept(sock_listen, NULL, NULL);
        service_handle(sock_connect);
        close(sock_connect);
    }

    return 0;
}

int service_handle(const int sock)
{
    int ret_val = 0;
    unsigned int sa_len = 0;
    struct sockaddr_in sa_peer;
    char str_ip[INET_ADDRSTRLEN] = {0};
    char buffer[MAX_MSG_BUF_SIZE] = {0};

    sa_len = SOCK_ADDR_SIZE;
    memset(&sa_peer, 0, SOCK_ADDR_SIZE);
    ret_val = getpeername(sock, (struct sockaddr *)&sa_peer, &sa_len);
    if(0 > ret_val)
    {
        fprintf(stderr, "call getsockname error.\n");
        return 1;
    }

    inet_ntop(AF_INET, &sa_peer.sin_addr, str_ip, INET_ADDRSTRLEN);
    printf("Get connected with %s:%d.\n", str_ip, ntohs(sa_peer.sin_port));

    snprintf(buffer, MAX_MSG_BUF_SIZE, "Talk about your history.");
    send(sock, buffer, strlen(buffer), 0);

    return 0;
}
