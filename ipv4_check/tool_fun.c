#include <stdio.h>
#include <stdint.h>

uint16_t getnchar(char *buf, size_t len)
{
    char c = '\0';
    uint16_t i = 0;
    uint16_t iTotal = 0;

    while((i < len) && ('\n' != (c = getchar())))
    {
        buf[i] = c;
        i++;
    }

    while('\n' != c)
    {
        c = getchar();
    }

    iTotal = i;
    return iTotal;
}
