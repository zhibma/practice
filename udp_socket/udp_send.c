#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef REMOTEIP
#error "Can't find macro defination of REMOTEIP."
#endif

#define SOCK_ADDR_SIZE      sizeof(struct sockaddr_in)
#define MSG_BUF_SIZE        256
#define REMOTEPORT          50034

int main()
{
    int sockfd = 0;
    int msg_len = 0;
    struct sockaddr_in addr;
    char msg[MSG_BUF_SIZE] = {0};

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("call socket");
        return 1;
    }

    memset(&addr, 0, SOCK_ADDR_SIZE);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(REMOTEPORT);
    inet_pton(AF_INET, REMOTEIP, &addr.sin_addr);

    msg_len = snprintf(msg, MSG_BUF_SIZE, "I have something to tell you.");
    sendto(sockfd, msg, msg_len, 0, (struct sockaddr *)&addr, SOCK_ADDR_SIZE);

    close(sockfd);
    return 0;
}
