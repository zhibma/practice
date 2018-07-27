#include <stdint.h>

int8_t ipv4_valid_check(char *str)
{
    uint8_t i = 0;
    uint8_t num = 0;
    uint8_t dot = 0;
    uint8_t len = 0;

    while((15 >= i) && ('\0' != str[i]))
    {
        if('0' <= str[i] && '9' >= str[i])num++;
        if('.' == str[i] && '.' != str[i + 1])dot++;
        i++;
    }

    len = i;
    if((7 > len) || (15 < len) || (3 != dot) || (3 != (len - num)))return 1;

    return 0;
}
