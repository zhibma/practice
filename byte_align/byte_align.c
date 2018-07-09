#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    short num1;
    unsigned num2;
    char payload[0];
}__attribute__ ((aligned(4))) str_t1_t;

typedef struct
{
    short num1;
    unsigned num2;
    char payload[0];
}__attribute__ ((packed)) str_t2_t;

int main()
{
    void *p_tmp;
    if(NULL == (p_tmp = (str_t1_t *)malloc(sizeof(str_t1_t) + 4)))
    {
	printf("Memory allocation failure.\n");
	return EXIT_FAILURE;
    }
    memset(p_tmp, 0, sizeof(str_t1_t) + 4);

    str_t1_t *p_val1 = (str_t1_t *)p_tmp;
    str_t2_t *p_val2 = (str_t2_t *)p_tmp;

    p_val1->num1 = 0x4241;
    p_val1->num2 = 0x48474645;
    p_val1->payload[0] = 'I';
    p_val1->payload[1] = 'J';
    p_val1->payload[2] = 'K';

    printf("        ------------------------------------------------------------------\n"
           "memory  |  A  |  B  |     |     |  E  |  F  |  G  |  H  |  I  |  J  |  K |\n"
           "        ------------------------------------------------------------------\n"
           "p_val1  |<--------->|           |<--------------------->|<-------------->|\n"
           "p_val2  |<--------->|<--------------------->|<-------------------------->|\n\n");

    printf("p_val1->num1:    %p %x\n", &p_val1->num1, p_val1->num1);
    printf("p_val1->num2:    %p %x\n", &p_val1->num2, p_val1->num2);
    printf("p_val1->payload: %p %s\n", p_val1->payload, p_val1->payload);
    printf("p_val2->num1:    %p %x\n", &p_val2->num1, p_val2->num1);
    printf("p_val2->num2:    %p %x\n", &p_val2->num2, p_val2->num2);
    printf("p_val2->payload: %p %s\n", p_val2->payload, p_val2->payload);

    putchar('\n');
    return 0;
}
