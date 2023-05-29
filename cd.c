#include "main.h"

char prevdir[100] = "";
char temp[100] = "";

void cd(char *path, char *home)
{
    strcpy(temp, prevdir);

    path = strtok(path, " \t");
    path = strtok(NULL, " \t");

    // printf("home is %s\n" , home);
    // printf("path is %s\n", path);

    if (path == NULL)
    {
        path = "~";
    }

    int flag = 0;
    char newpath[1000];

    if (path[0] == '~')
    {
        getcwd(prevdir, 200);
        char s[200] = "";
        char *t;
        // t stores the environment variable
        struct passwd *p;
        char *user = (char *)malloc(100);
        p = getpwuid(getuid());
        user = p->pw_name;

        t = user;

        // get the host name
        gethostname(s, 200);

        // printf("here111\n");
        char new[200];

        strcpy(new, home);
        strcat(new, path + 1);
        strcpy(newpath, new);
    }
    else if (path[0] == '-')
    {
        flag = 1;
        char *tempstr = "..";
        strcpy(newpath, prevdir);
        getcwd(prevdir, 200);
        // printf("home is %s\n", temp);
    }
    else
    {
        getcwd(prevdir, 200);
        // printf("here222\n");
        strcpy(newpath, path);
    }

    if (chdir(newpath) < 0)
    {
        // printf("here333\n");
        strcpy(prevdir, temp);
        printf("cd: %s: No such file or directory\n", path);
        return;
    }

    // printf("change - > %s\n" , newpath);
    char homme[200];
    getcwd(homme, 200);

    if (flag == 1)
        printf("%s\n", homme);
}