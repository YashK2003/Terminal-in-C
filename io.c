#include "main.h"

int readflag, overwriteflag, appendflag;
char outfile[200];
char infile[200];

void redirection(char *str)
{
    overwriteflag=0;
    readflag=0;
    appendflag=0;

    // printf("here: %s\n", str);
    str = strtok(str, " \t");
    char *bond[100];
    int count = 0;
    bond[count] = (char *)malloc(sizeof(char) * 300);
    strcpy(bond[count], str);
    count++;
    while (1)
    {
        str = strtok(NULL, " \t");

        if (str == NULL)
        {
            break;
        }

        bond[count] = (char *)malloc(sizeof(char) * 300);
        strcpy(bond[count], str);
        // printf("%d. %s\n", count, str);
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(bond[i], "<") == 0)
        {
            readflag = 1;
            strcpy(infile, bond[i + 1]);
        }

        if (strcmp(bond[i], ">") == 0)
        {
            overwriteflag = 1;
            strcpy(outfile, bond[i + 1]);
        }

        if (strcmp(bond[i], ">>") == 0)
        {
            appendflag = 1;
            strcpy(outfile, bond[i + 1]);
        }

        // printf("%d. %s\n", i, bond[i]);
    }

    // printf("readflag is %d\n", readflag);
    // printf("overwriteflag is %d\n", overwriteflag);
    // printf("appendflag is %d\n", appendflag);

    // if(readflag == 1)
    // printf("infile is %s\n", infile);

    // if(overwriteflag == 1 || appendflag == 1)
    // printf("outfile is %s\n", outfile);

    
}
