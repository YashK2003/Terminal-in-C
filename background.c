#include "main.h"

void bgfinal(char *str, char *home)
{
    // printf("str is %s\n",str);
    // time_t begin = time(NULL);

    str = strtok(str, " \t");

    char *bond[100];

    int count = 0;
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

    bond[count] = (char *)malloc(sizeof(char) * 300);
    bond[count] = NULL;
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%d. %s\n", i, bond[i]);
    // }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return;
    }
    else if (pid == 0)
    {
        setpgrp();
        execvp(bond[0], bond);
        exit(0);
    }
    else
    {
        for (int i = 1; i < 100; i++)
        {
            if (bgpid[i] == -1)
            {
                procbg[i] = (char *)malloc(sizeof(char) * 200);
                assert(procbg[i] != NULL);
                strcpy(procbg[i], bond[0]);
                bgpid[i] = pid;
                printf("[%d] %d\n", i, pid);
                break;
            }
        }
    }

    // time_t end = time(NULL);
    // int time_taken = (end - begin);

    // printf("fun() took %d seconds to execute \n", time_taken);
    return;
}