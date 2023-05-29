#include "main.h"

void pipeing(char *str, char *token, char *current_path, char *home)
{
    char *word;
    char **strparts = malloc(100 * sizeof(char *));

    word = strtok(str, "|");

    int x = 0;
    for (x = 0; word; ++x)
    {
        strparts[x] = word;
        word = strtok(NULL, "|");
    }

    strparts[x] = NULL;
    free(word);

    for (int i = 0; i < x; i++)
    {
        if (strparts[i][0] == ' ')
        {
            for (int j = 1; j < 50; j++)
            {
                strparts[i][j - 1] = strparts[i][j];
            }
        }
    }

    // for (int i = 0; i < x; i++)
    // {
    //     printf("--> %s\n", strparts[i]);
    // }

    int filedp[2], pos;
    int fs = 0;

    int countt = 0;
    for (int i = 0; strparts[i]; i++)
        countt++;

    pos = countt;
    int checkflag = pos - 1;

    // printf("l is %d\n" , l);
    if (pos > 1)
    {
        for (int x = 0; x < pos; x++)
        {
            pipe(filedp);

            // printf("--> %s\n", strparts[k]);
            if (!fork())
            {
                dup2(fs, 0);

                if (x != checkflag)
                {
                    dup2(filedp[1], 1);
                }

                close(filedp[0]);

                int in_temp = dup(0);
                int out_temp = dup(1);

                // MAIN THING
                // --------------------
                executecmds(strparts[x], current_path, home, 0);
                // printf("here is %s", strparts[k]);
                // --------------------

                dup2(in_temp, 0);
                dup2(out_temp, 1);

                exit(0);
            }

            wait(NULL);
            close(filedp[1]);
            fs = filedp[0];
        }
    }

    free(strparts);
}


// cat < in.txt | wc > out.txt ; echo hello world ; cat pipe.c


