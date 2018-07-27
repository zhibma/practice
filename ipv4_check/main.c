#include <stdio.h>
#include <string.h>
#include "tool_fun.h"
#include "ipv4_check.h"

#define MAX_LINE_SIZE   256

int main()
{
    char str_ip[MAX_LINE_SIZE] = {0};

    printf("Input the ip adress: ");
    getnchar(str_ip, MAX_LINE_SIZE - 1);

    if(0 != ipv4_valid_check(str_ip))
    {
        fprintf(stderr, "Invalid string of ip adress.\n");
        return 1;
    }

    printf("Accept your ip adress [%s].\n", str_ip);

    return 0;
}
