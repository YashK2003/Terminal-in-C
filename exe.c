#include "main.h"

int doneflag;

void executecmds(char *call, char *current_path, char *home, int flag)
{
    // printf("call is %s\n", call);

    doneflag = 0;
    char *s = (char *)malloc(sizeof(char) * 100);
    strcpy(s, call);

    // *************************************
    
    int temp = strlen(s);
    // temp = temp - 1;
    // s[temp] = '\0';

    // *************************************

    // count the number of semicolons
    int colons = 0;
    for (int i = 0; i < temp; i++)
    {
        if (s[i] == ';')
            colons++;
    }
    // printf("%d\n", colons);
    char ins[200];
    strcpy(ins, s);
    // printf("s is --> %s\n", s);
    int templen = strlen(ins);
    for (int i = 0; i < templen - 1; i++)
    {
        if (ins[i] == '<' || ins[i] == '>' || (ins[i] == '>' && ins[i + 1] == '>'))
        {
            redirection(ins);
            break;
        }
    }

    if (readflag == 0)
    {
        for (int i = 0; i < templen - 1; i++)
        {
            if (ins[i] == '>' || (ins[i] == '>' && ins[i + 1] == '>'))
            {
                s[i] = '\0';
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < templen - 1; i++)
        {
            if (ins[i] == '<')
            {
                s[i] = ' ';
            }
            if (ins[i] == '>' || (ins[i] == '>' && ins[i + 1] == '>'))
            {
                s[i] = '\0';
                break;
            }
        }
    }
    // printf("in exe s is --> %s\n", s);
    // for taking the input commands
    char command[200][200];

    int numberOfCommands = 0;

    // break the string with semicolons
    char *token = strtok(s, ";");
    while (token != NULL)
    {
        strcpy(strcat(command[numberOfCommands++], "\0"), token);
        token = strtok(NULL, ";");
    }

    char str[500];

    for (int k = 0; k < colons + 1; ++k)
    {
        doneflag = 0;
        // printf("%d , original is %s\n",k, command[k]);
        // HERE BREAK THE STRING INTO VARIOUS COMMANDS
        int counter = 0;
        int yt = strlen(command[k]);
        int j = 0;
        while (command[k][j] == ' ' || command[k][j] == '\t')
            j++;
        for (; j <= yt; j++)
        {
            s[counter] = command[k][j];
            counter++;
        }

        // printf("s is --> %s\n", s);
        // CHECK FOR INPUT OUTPUT REDIRECTION

        int tempvart, fd;
        if (overwriteflag)
        {
            tempvart = dup(1);
            fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (appendflag)
        {
            tempvart = dup(1);
            fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
            lseek(fd, 0, SEEK_END);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        // IMPLEMENTATION OF CD
        // =====================
        char *cdstr = "cd";
        char cdcompare[15];
        for (int j = 0; j < 2; j++)
            cdcompare[j] = s[j];

        cdcompare[2] = '\0';
        if (strcmp(cdcompare, cdstr) == 0 && (s[2] == ' ' || s[2] == '\t'))
        {
            doneflag = 1;
            cd(s, current_path);
            // continue;
        }
        else if ((strcmp(cdcompare, cdstr) == 0 && s[2] != ' '))
        {
            printf("Invalid command\n");
            continue;
        }
        // =====================

        // IMPLEMENTATION OF QUIT
        // =====================
        char *quitstr = "quit";
        char quitcompare[15];
        for (int j = 0; j < 4; j++)
            quitcompare[j] = s[j];

        quitcompare[4] = '\0';
        if (strcmp(quitcompare, quitstr) == 0)
        {
            exit(0);
        }
        // =====================

        // IMPLEMENTATION OF ECHO
        // =====================
        char echocompare[15];
        for (int j = 0; j < 4; j++)
            echocompare[j] = s[j];
        echocompare[4] = '\0';
        char *echostr = "echo";
        if (strcmp(echocompare, echostr) == 0 && s[4] == ' ')
        {
            doneflag = 1;
            echocmd(s);
            // continue;
        }
        else if ((strcmp(echocompare, echostr) == 0 && s[4] != ' '))
        {
            printf("Invalid command\n");
            continue;
        }

        // =====================

        // IMPLEMENTATION OF PWD
        // =====================
        char pwdcompare[15];
        for (int j = 0; j < 3; j++)
            pwdcompare[j] = s[j];
        pwdcompare[3] = '\0';
        char *pwdstr = "pwd";
        if (strcmp(pwdcompare, pwdstr) == 0 && strlen(s) == 3)
        {
            doneflag = 1;
            pwdcmd();
            // continue;
        }
        else if ((strcmp(pwdcompare, pwdstr) == 0 && strlen(s) != 3))
        {
            int lentemp = strlen(s), flagg = 0;
            for (int i = 3; i <= 3; i++)
            {
                if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
                {
                    printf("Invalid command\n");
                    flagg = 1;
                    break;
                }
            }
            if (flagg == 0)
            {
                doneflag = 1;
                pwdcmd();
                // continue;
            }
        }
        // =====================

        // IMPLEMENTATION OF LS
        // =====================
        char lscompare[15];
        for (int j = 0; j < 2; j++)
            lscompare[j] = s[j];

        lscompare[2] = '\0';
        char *lsstr = "ls";

        if (strcmp(lscompare, lsstr) == 0)
        {
            doneflag = 1;
            splitls(s, home);
            // continue;
        }

        // =====================

        // IMPLEMENTATION OF PINFO
        // =====================
        char pinfocompare[15];
        for (int j = 0; j < 5; j++)
            pinfocompare[j] = s[j];

        pinfocompare[5] = '\0';
        char *pinfostr = "pinfo";

        if (strcmp(pinfocompare, pinfostr) == 0)
        {
            doneflag = 1;
            pinfo(s, home);
            // continue;
            // s[0] = '\0';
        }

        // =====================

        // IMPLEMENTATION OF HISTORY
        // =====================
        char hiscompare[15];
        for (int j = 0; j < 7; j++)
            hiscompare[j] = s[j];
        hiscompare[7] = '\0';
        char *hisstr = "history";
        // if (strcmp(hiscompare, hisstr) == 0)
        // {
        //     print_history(home);
        //     // s[0] = '\0';
        // }

        if (strcmp(hiscompare, hisstr) == 0 && strlen(s) == 7)
        {
            doneflag = 1;
            print_history(home);
            // continue;
        }
        else if ((strcmp(hiscompare, hisstr) == 0 && strlen(s) != 7))
        {
            int lentemp = strlen(s), flagg = 0;
            for (int i = 7; i < lentemp; i++)
            {
                if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
                {
                    printf("Invalid command\n");
                    flagg = 1;
                    break;
                }
            }
            if (flagg == 0)
            {
                doneflag = 1;
                print_history(home);
                // continue;
            }
        }
        // =====================

        // IMPLEMENTATION OF FG
        // =====================
        char fgcompare[15];
        for (int j = 0; j < 2; j++)
            fgcompare[j] = s[j];
        fgcompare[2] = '\0';
        char *fgstr = "fg";
        if (strcmp(fgcompare, fgstr) == 0)
        {
            bgtofg(s);
            continue;
        }
        else if ((strcmp(fgcompare, fgstr) == 0 && s[2] != ' '))
        {
            printf("Invalid command\n");
            continue;
        }
        // =====================

        // IMPLEMENTATION OF BG
        // =====================
        char bgcompare[15];
        for (int j = 0; j < 2; j++)
            bgcompare[j] = s[j];
        bgcompare[2] = '\0';
        char *bgstr = "bg";
        if (strcmp(bgcompare, bgstr) == 0)
        {
            bgbtobgf(s);
            continue;
        }
        else if ((strcmp(bgcompare, bgstr) == 0 && s[2] != ' '))
        {
            printf("Invalid command\n");
            continue;
        }
        // =====================

        // IMPLEMENTATION OF JOBS
        // =====================
        char jobscompare[15];
        for (int j = 0; j < 4; j++)
            jobscompare[j] = s[j];
        jobscompare[4] = '\0';
        char *jobsstr = "jobs";
        if (strcmp(jobscompare, jobsstr) == 0)
        {
            jobs("..", "..", 1);
            // continue;
        }
        else if ((strcmp(jobscompare, jobsstr) == 0 && s[4] != ' '))
        {
            printf("lolInvalid command\n");
            continue;
        }
        // =====================

        // IMPLEMENTATION OF SIG
        // =====================
        char sigcompare[15];
        for (int j = 0; j < 3; j++)
            sigcompare[j] = s[j];
        sigcompare[3] = '\0';
        char *sigstr = "sig";
        if (strcmp(sigcompare, sigstr) == 0)
        {
            char jobno[20];
            int jobnum = 0;
            while (s[jobnum + 4] != ' ')
            {
                jobno[jobnum] = s[jobnum + 4];
                jobnum++;
            }
            jobno[jobnum] = '\0';

            int topassjobnum = atoi(jobno);
            // printf("kill it bro! %d \n", topassjobnum);

            char signlno[20];
            int sigyt = 0;
            while (s[jobnum + 5] != ' ' && s[jobnum + 5] != '\n')
            {
                signlno[sigyt] = s[jobnum + 5];
                jobnum++;
                sigyt++;
            }
            signlno[jobnum] = '\0';

            int topasssignlnum = atoi(signlno);
            // printf("kill it bro! %d \n", topasssignlnum);
            sigkill(topassjobnum, topasssignlnum);

            // continue;
        }
        else if ((strcmp(sigcompare, sigstr) == 0 && s[3] != ' '))
        {
            printf("lolInvalid command\n");
            continue;
        }
        // =====================

        // IMPLEMENTATION OF DISCOVER
        // =====================
        char dvrcompare[22];
        for (int j = 0; j < 8; j++)
            dvrcompare[j] = s[j];
        dvrcompare[8] = '\0';
        char *dvrstr = "discover";
        if (strcmp(dvrcompare, dvrstr) == 0)
        {
            doneflag = 1;
            char teo[200];
            getcwd(teo, 200);
            show_dir_content(teo, s, home);
            // continue;
            // s[0] = '\0';
        }
        // =====================

        if (strlen(command[k]) == 0)
            continue;

        if (doneflag == 0)
        {
            doneflag = 1;
            execute(command[k], home);
        }

        if (overwriteflag || appendflag)
        {
            dup2(tempvart, STDOUT_FILENO);
            close(tempvart);
        }
    }

    for (int i = 0; i < 100; i++)
    {
        command[i][0] = '\0';
    }

    free(s);
}