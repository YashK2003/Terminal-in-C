#include "main.h"

void echocmd(char *str)
{
    // remove the tab part
    str = strtok(str, " \t");
    str = strtok(NULL, " \t");

    while (str != NULL)
    {

        int n = strlen(str);

        // printf("%d \n" , n);

        for (int i = 0; i < n; i++)
        {

            {
                printf("%c", str[i]);
            }
        }

        printf(" ");
        str = strtok(NULL, " \t");
    }
    printf("\n");
}