#include "main.h"
char pid[200];
char cur[250];

int printpid(char *token)
{
    if (token == NULL)
    {
        int temp = getppid();
        sprintf(pid, "%d", temp);
    }
    else
    {
        strcpy(pid, token);
        // printf("token after is %s\n", token);
    }

    strcpy(cur, "/proc/");
    strcat(cur, pid);
    // printf("--> %s\n", cur);
    char pstat[250];
    strcpy(pstat, cur);
    strcat(pstat, "/stat");

    // printf("--> %s\n", pstat);

    FILE *file = fopen(pstat, "r");
    if (file == NULL)
    {
        printf("No process with pid: %s\n", pid);
        return 0;
    }
    else
    {
        printf("pid : %s\n", pid);
        return 1;
    }
}

void printmemory(char *token)
{
    char memstat[250];
    strcpy(memstat, cur);
    strcat(memstat, "/statm");

    FILE *file = fopen(memstat, "r");

    char toprintmemstat[150] = "";

    fscanf(file, "%s", toprintmemstat);

    printf("memory : %s {Virtual Memory}\n", toprintmemstat);

    return;
}

void tildacompression(char *tocmps, char *home)
{
    // printf("--->  %s\n", home);
    // printf("--->  %s\n", tocmps);

    int length1 = strlen(home);
    int length2 = strlen(tocmps);

    if (length2 < length1)
    {
        printf("Executable Path : %s\n", tocmps);
        return;
    }
    else
    {
        int flag = 0;
        for (int i = 0; i < length1; i++)
        {
            if (tocmps[i] != home[i])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            printf("Executable Path : %s\n", tocmps);
            return;
        }

        char printtemp[300];
        strcpy(printtemp, tocmps + length1);
        printf("Executable Path : ~%s\n", printtemp);

        return;
    }
}

void executepath(char *token, char *home)
{
    char exestat[250] = "";
    strcpy(exestat, cur);
    strcat(exestat, "/exe");

    char toprintexestat[300] = "";
    readlink(exestat, toprintexestat, 300);

    // printf("--> %s\n", toprintexestat);

    tildacompression(toprintexestat, home);
}

void process_status(char *token)
{
    char stat[250] = "";
    strcpy(stat, cur);
    strcat(stat, "/status");
    FILE *fp = fopen(stat, "r");

    int counter = 0;
    char cmp1temp[250];
    char cmp2temp[250];
    char *line = NULL;
    long unsigned int len = 0;
    long unsigned int input;

    while ((input = getline(&line, &len, fp)) != -1)
    {
        counter++;
        if (counter == 3)
        {
            printf("Process Status : %c", line[7]);
        }

        if (counter == 4)
        {
            strcpy(cmp1temp, line);
        }

        if (counter == 6)
        {
            strcpy(cmp2temp, line);
        }

        // printf("Retrieved line of length %zu:\n", input);
        // printf("%s", line);
    }
    fclose(fp);

    if (strcmp(cmp2temp + 1, cmp1temp + 2) == 0)
        printf("\n");
    else
        printf("+\n");

    // printf("1. -> %s\n" , cmp1temp);
    // printf("2. -> %s\n" , cmp2temp);
}

void pinfo(char *token, char *home)
{
    // printf("token before is %s\n", token);
    token = strtok(token, " \t");
    token = strtok(NULL, " \t");
    // printf("token after is %s\n", token);

    int ret_val = printpid(token);

    if (ret_val == 0)
        return;

    printmemory(token);

    process_status(token);

    executepath(token, home);

    return;
}