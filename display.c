#include "main.h"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"

int timeprint;
char help1[300];

int checkifnotequal(char *home, char *curPath, char *t, char *s, int flagno, char *prex)
{
    int num1 = strlen(home);
    int num2 = strlen(curPath);

    if (num1 != num2)
    {
        printf(YELLOW "<%s@%s:" CYAN "%s> "
                      "\x1b[0m",
               t, s, curPath);
        return 1;
    }

    return 0;
}

void complex1(char *home, char *curPath, char *t, char *s, int flagno, char *prex)
{
    // printf("--> %s <--\n", prex);
    int length1 = strlen(home);
    int length2 = strlen(curPath);

    if (length2 < length1)
    {
        if (timeprint == 0)
            printf(YELLOW "<%s@%s:" CYAN "%s> "
                          "\x1b[0m",
                   t, s, curPath);
        else
            printf(YELLOW "<%s@%s:" CYAN "%stook %ds> "
                          "\x1b[0m",
                   t, s, curPath, timeprint);
    }
    else
    {
        char printtemp[300];
        strcpy(printtemp, curPath + length1);

        if (timeprint == 0)
            printf(YELLOW "<%s@%s:" CYAN "~%s> "
                          "\x1b[0m",
                   t, s, printtemp);
        else
            printf(YELLOW "<%s@%s:" CYAN "~%stook %ds> "
                          "\x1b[0m",
                   t, s, printtemp, timeprint);
    }

    if (flagno == -7)
    {
        printf("%s", prex);
        // printf("here i am lolololol");
    }

    return;
}

void display(char *home, int specflag, char *extrapr1, char *extrapr2)
{
    timeprint = specflag;
    char s[200] = "";
    char *t;
    char curPath[200] = "";

    // t stores the environment variable
    struct passwd *p;
    char *user = (char *)malloc(100);
    p = getpwuid(getuid());
    user = p->pw_name;

    t = user;

    // get the host name
    gethostname(s, 200);

    // current working directory
    getcwd(curPath, 200);

    //  printf("home is %s\n", home);
    //  printf("curpath is %s\n", curPath);

    // Checking if in same home or not
    // int flag = checkifnotequal(home, curPath, t, s);

    // if (flag == 1)
    // return;
    //
    if (timeprint < 0)
        timeprint = 0;
    complex1(home, curPath, t, s, specflag, extrapr1);

    // printf("%s %s %d %d\n", curPath, home, num1, num2);

    return;
}