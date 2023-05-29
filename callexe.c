#include "main.h"

int execute(char *str, char *home)
{
    
    // printf("str is %s\n", str);
    int passcount = 0;
    str = strtok(str, " \t");
    char *bonrd[100];
    int count = 0;
    bonrd[count] = (char *)malloc(sizeof(char) * 300);
    strcpy(bonrd[count], str);
    count++;

    while (1)
    {
        str = strtok(NULL, " \t");

        if (str == NULL)
        {
            break;
        }

        bonrd[count] = (char *)malloc(sizeof(char) * 300);
        strcpy(bonrd[count], str);
        // printf("%d. %s\n", count, str);
        count++;
    }

    bonrd[count] = (char *)malloc(sizeof(char) * 300);
    bonrd[count] = NULL;
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%d. %s\n", i, bonrd[i]);
    // }


    char *parapass[300];

    for (int i = 0; i < count; i++)
    {
        if (strcmp(bonrd[i], "&") == 0)
        {
            parapass[passcount] = (char *)malloc(sizeof(char) * 300);
            strcpy(parapass[passcount], "NULL");

            // NOW CALL BG
            char *fgparameter;
            fgparameter = (char *)malloc(sizeof(char) * 300);
            strcpy(fgparameter, "bg ");
            for (int i = 0; i < passcount; i++)
            {
                strcat(fgparameter, parapass[i]);
                strcat(fgparameter, " ");
            }
            bgfinal(fgparameter, home);

            // FREE SPACE
            for (int i = 0; i <= passcount; i++)
            {
                free(parapass[i]);
            }
            passcount = 0;
        }
        else
        {
            parapass[passcount] = (char *)malloc(sizeof(char) * 300);
            strcpy(parapass[passcount], bonrd[i]);
            passcount++;
        }
    }

    // printf("count 1 is : %d\n", passcount);

    if (passcount != 0)
    {
        // NOW CALL FG
        char *fgparameter;
        fgparameter = (char *)malloc(sizeof(char) * 300);
        strcpy(fgparameter, "fg ");
        for (int i = 0; i < passcount; i++)
        {
            strcat(fgparameter, parapass[i]);
            strcat(fgparameter, " ");
        }

        int val = fg(fgparameter, home);
        return val;
        // printf("val is %d\n", val);
    }

    return -1;
}
