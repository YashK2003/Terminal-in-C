#include "main.h"

// int bgpid[500];
// char *procbg[200];

char pronames[200][50];
int cntnames[100];
int pidnames[100];

void sortStrings(int n, int token)
{
    char temp[100];
    int tempcnt;
    int temppid;

    // printf("--> %d\n", token);

    // Sorting strings using bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(pronames[j], pronames[j + 1]) > 0)
            {
                strcpy(temp, pronames[j]);
                strcpy(pronames[j], pronames[j + 1]);
                strcpy(pronames[j + 1], temp);

                tempcnt = cntnames[j];
                cntnames[j] = cntnames[j + 1];
                cntnames[j + 1] = tempcnt;

                temppid = pidnames[j];
                pidnames[j] = pidnames[j + 1];
                pidnames[j + 1] = temppid;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        char pid[50];
        char tempstr[50] = "/proc/";

        sprintf(pid, "%d", pidnames[i]);

        strcat(tempstr, pid);

        strcat(tempstr, "/stat");

        FILE *file = fopen(tempstr, "r");

        char firstpara[100];
        char secondpara[100];
        char thirdpara[100];

        fscanf(file, "%s %s %s", firstpara, secondpara, thirdpara);

        if (strcmp(thirdpara, "T") == 0 && token != 5)
        {
            printf("[%d] ", cntnames[i]);
            printf("Stopped %s [%d]\n", pronames[i], pidnames[i]);
        }
        else if (strcmp(thirdpara, "T") != 0 && token != 4)
        {
            printf("[%d] ", cntnames[i]);
            printf("Running %s [%d]\n", pronames[i], pidnames[i]);
        }
    }
}

void jobs(char *call1, char *call2, int token)
{
    // for (int i = 1; i < 10; i++)
    // {
    //     printf("--> %d\n", bgpid[i]);
    // }

    int np = 0;

    for (int i = 1; i < 50; i++)
    {
        if (bgpid[i] != -1)
        {
            
            np++;

            char tempstr[50] = "/proc/";

            char pid[50];

            sprintf(pid, "%d", bgpid[i]);

            strcat(tempstr, pid);

            strcat(tempstr, "/stat");

            FILE *file = fopen(tempstr, "r");

            char firstpara[100];
            char secondpara[100];
            char thirdpara[100];

            fscanf(file, "%s %s %s", firstpara, secondpara, thirdpara);

            if (strcmp(thirdpara, "T") == 0 && token != 5)
            {

                strcpy(pronames[np - 1], procbg[i]);
                cntnames[np - 1] = np;
                pidnames[np - 1] = bgpid[i];
                // printf("[%d] ", np);
                // printf("Stopped %s [%d]\n", procbg[i], bgpid[i]);
            }
            else if (strcmp(thirdpara, "T") != 0 && token != 4)
            {

                strcpy(pronames[np - 1], procbg[i]);
                cntnames[np - 1] = np;
                pidnames[np - 1] = bgpid[i];
                // printf("[%d] ", np);
                // printf("Running %s [%d]\n", procbg[i], bgpid[i]);
            }
        }
    }

    sortStrings(np, token);

    // sleep 150 & nano & gedit & sleep 100 &
    // for (int i = 0; i < np; i++)
    // {
    //     printf("[-> %d] ", cntnames[i]);
    //     printf("  %s [-> %d]\n", pronames[i], pidnames[i]);
    // }
}
