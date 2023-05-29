#include "main.h"

void sigkill(int jobno, int signo)
{
    // printf("jobno is %d\n", jobno);
    // printf("signo is %d\n", signo);

    if (bgpid[jobno] == -1 || jobno >= 60)
    {
        printf("no job with the given number exists\n");
        return;
    }

    kill(bgpid[jobno], signo);

    return;
}

void bgtofg(char *str)
{

    // printf("str is %s\n", str);
    char jobno[200];
    int jobnum = 0;
    while (str[jobnum + 3] != ' ' && str[jobnum + 3] != '\n')
    {
        jobno[jobnum] = str[jobnum + 3];
        jobnum++;
    }
    jobno[jobnum] = '\0';

    int num = atoi(jobno);

    // printf("num is %d\n", num);

    if (bgpid[num] == -1 || num >= 60)
    {
        printf("no job with the given number exists\n");
        return;
    }

    for (int i = 1; i <= 50; i++)
    {
        if (i == num)
        {

            signal(SIGTTIN, SIG_IGN);

            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, bgpid[num]);

            kill(bgpid[num], SIGCONT);
            bgpid[num] = -1;

            waitpid(-1, NULL, WUNTRACED);

            tcsetpgrp(STDIN_FILENO, getpgrp());

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }

    return;
}

void bgbtobgf(char *str)
{
    char jobno[200];
    int jobnum = 0;
    while (str[jobnum + 3] != ' ' && str[jobnum + 3] != '\n')
    {
        jobno[jobnum] = str[jobnum + 3];
        jobnum++;
    }
    jobno[jobnum] = '\0';

    int num = atoi(jobno);

    // printf("num is %d\n", num);
    if (bgpid[num] == -1 || num >= 60)
    {
        printf("no job with the given number exists\n");
        return;
    }

    for (int i = 1; i <= 50; i++)
    {
        if (i == num)
        {
            kill(bgpid[num], SIGTTIN);
            kill(bgpid[num], SIGCONT);
        }
    }

    return;
}