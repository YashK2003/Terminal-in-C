#include "main.h"
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
char joincom[200];

void die(const char *s)
{
    // perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        // die("");
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        // die("");
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        // die("");
        die("tcsetattr");
}

int inputread(char *call, char *path, char *home, char *extra1)
{

    // printf("\nInput Read: [%s]", inp);
    setbuf(stdout, NULL);
    enableRawMode();
    int pt = 0;

    if (captain == 1)
    {
        strcpy(inp, steve);
        captain = 0;
        // printf("here %s \n", inp);
        pt = strlen(inp);
    }

    // memset(inp, '\0', 100);

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            if (c == 10)
                break;
            else if (c == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                { // length of escape code
                    printf("\rarrow key: %s", buf);
                }
            }
            else if (c == 127)
            { // backspace
                if (pt > 0)
                {
                    if (inp[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    inp[--pt] = '\0';
                    printf("\b \b");
                }
            }
            else if (c == 9)
            { // TAB character
                inp[pt++] = c;

                // OPERATE IN STRING TO EXTRACT THE GIVEN CHARACTER
                // printf("--> %s\n" , inp);
                int yt = strlen(inp), j = 0;
                char topass[200];
                int slashflag = 0;

                // FIRST DETECT TILL SPACE WHAT IS THE COUNT
                int spacecount = yt - 1;
                for (int i = yt - 1; i >= 0; i--)
                {
                    if (inp[i] == ' ')
                        break;
                    spacecount--;
                }

                // printf("--> %d\n" , spacecount);

                // NOW DO THE COUNTING OF / CHARACTER
                for (int i = yt - 1; i >= 0; i--)
                {
                    if (inp[i] == '/')
                    {
                        slashflag = 1;
                    }

                    if (inp[i] == ' ' || inp[i] == '/')
                        break;
                    topass[j] = inp[i];
                    j++;
                }
                topass[j] = '\0';

                // printf("%d\n" , slashflag);

                char helpplease[200] = "";

                if (slashflag == 1)
                {
                    int runlop = yt - j;
                    for (int i = spacecount + 1; i < runlop; i++)
                    {
                        helpplease[i - spacecount - 1] = inp[i];
                    }
                    helpplease[runlop] = '\0';
                }

                // printf("\nit is -->  %s\n", helpplease);
                yt = j;
                j = 0;
                char bondpass[200];
                for (int i = yt - 1; i >= 0; i--)
                {
                    bondpass[j] = topass[i];
                    j++;
                }
                bondpass[j] = '\0';

                for (int i = 0; i < j; i++)
                {
                    if (bondpass[i] == '\t' || bondpass[i] == ' ' || bondpass[i] == '\n')
                    {
                        bondpass[i] = '\0';
                        break;
                    }
                }

                // printf("\nbondpass is %s\n", bondpass);

                // char current_path[200];
                // getcwd(current_path, 200);

                strcpy(tomcr, inp);
                // printf("--> %s\n", inp);
                int tempu = runstore(helpplease, bondpass, home);
                if (tempu == 7)
                {
                    // printf("==> %s\n" , help1);
                    return 7;
                }

                int inplen = strlen(inp);
                if (inp[inplen - 1] == '\t')
                    inp[inplen - 1] = '\0';
                // printf("\n joincom is %s\n" , joincom);
                // printf("\n inp is %s\n" , inp);

                strcat(inp, joincom);
                pt = strlen(inp);

                // if (tempu == 11)
                // {
                //     // printf("==> %s\n" , help1);
                //     return 11;
                // }

                // if (tempu == 11)
                // {
                //     // printf("==> %s\n" , help1);
                //     return 11;
                // }
                // // printf("\nInput Read: [%s]\n", bondpass);
                // for (int i = 0; i < 8; i++)
                // { // TABS should be 8 spaces
                // printf("tab spaced!!");
                // }
            }
            else if (c == 4)
            {
                exit(0);
            }
            else
            {
                printf("%d\n", c);
            }
        }
        else
        {
            inp[pt++] = c;
            printf("%c", c);
        }
    }
    disableRawMode();

    // printf("\nInput Read: [%s]\n", inp);
    strcpy(getinp, inp);
    // printf("\ngetinp is %s\n", getinp);
    memset(joincom, 0, 200);
    memset(inp, 0, 200);
    return 2;
    // printf("\nInput Read: [%s]\n", inp);
}