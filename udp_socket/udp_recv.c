#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_ADDR_SIZE      sizeof(struct sockaddr_in)
#define MSG_BUF_SIZE        256
#define LOCALPORT           50034

int main()
{
    int sockfd = 0;
    struct sockaddr_in addr;
    socklen_t sa_len = SOCK_ADDR_SIZE;
    char str_ip[INET_ADDRSTRLEN] = {0};
    char msg[MSG_BUF_SIZE] = {0};

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("call socket");
        return 1;
    }

    memset(&addr, 0, SOCK_ADDR_SIZE);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LOCALPORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&addr, SOCK_ADDR_SIZE) < 0)
    {
        perror("call bind");
        return 1;
    }

    while(1)
    {
        recvfrom(sockfd, msg, MSG_BUF_SIZE, 0, (struct sockaddr *)&addr, &sa_len);
        inet_ntop(AF_INET, &addr.sin_addr, str_ip, INET_ADDRSTRLEN);
        printf("received message from %s:%d.\n", str_ip, ntohs(addr.sin_port));
        printf("#### %s ####\n\n", msg);
    }

    close(sockfd);
    return 0;
}
