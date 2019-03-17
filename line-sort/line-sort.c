/* A demo to sort content of file by line. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
    char a[400][80] = {{0}};
    FILE *fp = NULL;
    short i = 0;
    short j = 0;

    if(2 != argc)
    {
        printf("Error: need a argument.\n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r+");
    if(NULL == fp)
    {
        printf("Error: open file for read, not exist?\n");
        return EXIT_FAILURE;
    }

    while(0 == feof(fp) && i < 400 - 1)
    {
        fgets(a[i], 80, fp);
        /* blank line fix */
        if(0 != a[i][0])
        {
            i++;
        }
    }
    fclose(fp);

    while(--i > 0)
    {
        for(j = i - 1; j >= 0; j--)
        {
            if(0 > strncmp(a[i], a[j], 80))
            {
                strncpy(a[400 - 1], a[j], 80);
                strncpy(a[j], a[i], 80);
                strncpy(a[i], a[400 - 1], 80);
                memset(a[400 - 1], 0, 80);
            }
        }
    }

    while(0 != a[i][0])
    {
        fprintf(stdout, "%s", a[i++]);
    }

    return EXIT_SUCCESS;
}
