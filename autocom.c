#include "main.h"

#define NORMAL_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1b[0m"

int yt = 0;
int count = 0;
char contents[1000][200];
char joincom[200];

void autostore(char *path, int flag, char *token)
{
    // printf("flag is : %d\n", flag);
    // printf("path is : %s \n", path);
    struct dirent **namelist = NULL;

    int n, i = 0;
    n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0)
        return;
    else
    {
        while (i < n)
        {
            struct stat st_buf;

            char d_path[300]; // here I am using sprintf which is safer than strcat
            sprintf(d_path, "%s/%s", path, namelist[i]->d_name);

            stat(d_path, &st_buf);
            if (S_ISREG(st_buf.st_mode))
            {
                // printf("%s\n", d_path + yt);
                strcpy(contents[count], d_path + yt);
                count++;
            }
            if (S_ISDIR(st_buf.st_mode))
            {
                if (namelist[i]->d_name[0] == '.')
                {
                    i++;
                    continue;
                }

                // printf("%s\n", d_path + yt);
                strcpy(contents[count], d_path + yt);
                count++;
                // autostore(d_path, flag, token);
                // printf("bvjwv\n");
            }

            i++;
        }
        // free(namelist[i]);
    }
}

int runstore(char *path, char *call, char *home)
{
    // // printf("her\n");
    // if (strcmp(call, "ma") == 0)
    // {
    //     printf("YES\n");
    // }
    // elsedisplay(home, val);
    // {
    //     printf("NO\n");
    // }

    count = 0;
    char pathpath[250];

    if (strlen(path) == 0)
        getcwd(pathpath, 250);
    else
        strcpy(pathpath, path);

    // printf("\n-->path is %s\n", path);

    yt = strlen(pathpath) + 1;

    autostore(pathpath, 0, home);

    // printf("path is : %s\n", pathpath);

    // for (int i = 0; i < count; i++)
    // {
    //     printf("-->   %s\n", contents[i]);
    // }
    // printf("%d\n", count);

    int temp = strlen(call);
    char matched[100][200];
    int matchescount = 0;
    int flag = 0;
    for (int i = 0; i < count; i++)
    {
        flag = 0;
        for (int j = 0; j < temp; j++)
        {
            if (call[j] != contents[i][j])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            strcpy(matched[matchescount], contents[i]);
            matchescount++;
        }
    }

    if (matchescount == 0)
    {
        return 3;
    }

    int important = 0;

    if (matchescount == 1)
    {
        int temp = strlen(call);
        // printf("%s", matched[0] + temp);
        strcpy(joincom, matched[0] + temp);

        char joincallcom[200];
        strcpy(joincallcom, call);
        strcat(joincallcom, joincom);
        // printf("\n--> %s" , joincallcom);
        struct stat st_buf;
        stat(joincallcom, &st_buf);
        if (S_ISDIR(st_buf.st_mode))
        {
            printf("%s/", matched[0] + temp);
            strcat(joincallcom, "/");
        }
        else
            printf("%s", matched[0] + temp);

        // goto end;
        strcpy(help1, joincallcom);
        // printf("it is : %s   \n", joincallcom);

        return 11;
    }

    // FIND THE LENGTH OF MINIMUM WORD
    int minlen = 10000;
    for (int i = 0; i < matchescount; i++)
    {
        if (minlen > strlen(matched[i]))
            minlen = strlen(matched[i]);
    }

    // IF FOUND MULTIPLE MATCHES CHECK PREFIX
    int idx = 0;
    for (int x = 0; x < minlen; x++)
    {
        for (int i = 0; i < matchescount - 1; i++)
        {
            if (matched[i][x] != matched[i + 1][x])
            {
                idx = x - 1;
                goto end;
            }
            // printf("\n%s", matched[i]);
        }
    }

end:;

    // printf("idx is %d\n", idx);
    printf("\n");
    for (int i = 0; i < matchescount; i++)
    {
        if (i == matchescount - 1)
            printf("%s", matched[i]);
        else
            printf("%s\n", matched[i]);
    }

    // printf("idx is %d\n", idx);
    // display(home, 0, "no", "no");

    // here:;
    // printf("ekjvbw");

    char yyy[100];
    strcpy(yyy, tomcr);
    int yct = strlen(tomcr);
    tomcr[yct - 1] = '\0';

    // display(home, 0,tomcr , "no");
    strcpy(help1, tomcr);
    // printf("here it is --> %s\n", tomcr);

    // printf("--> %d\n", temp);
    // printf("--> %c\n", matched[0][0]);
    // printf("--> %c\n", matched[0][1]);

    int lastm = strlen(help1);
    // lastm--;
    int ryt = strlen(inp);
    for (int i = temp; i <= idx; i++)
    {
        // printf("\n--> %d", idx);

        // printf("%c", matched[0][i]);
        help1[lastm] = matched[0][i];
        lastm++;
        yyy[yct] = matched[0][i];
        yct++;
        inp[ryt - 1] = matched[0][i];
        ryt++;
    }
    help1[lastm] = '\0';
    inp[ryt] = '\0';
    // printf("--> %s\n", help1);

    return 7;
}
