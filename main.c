#include "main.h"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"

int myid;
char getinp[300];
int doneflag = 0;
int directflag = 0;
int val = 0;
char home[200];
int readflag, overwriteflag, appendflag;
char help1[300];

int captain;
char steve[300];

void ctrlcfunc()
{
    return;
}

void bgprocprint()
{
    int status;
    int a = waitpid(-1, &status, WNOHANG);
    int idx = 0;
    for (int i = 1; i < 50; i++)
    {
        if (bgpid[i] == a)
        {
            bgpid[i] = -1;
            idx = i;
            break;
        }
    }
    // for(int i=0 ; i)
    if (a > 0)
    {
        if (WIFSTOPPED(status))
            return;

        printf("\n%s with pid = %d exited normally\n", procbg[idx], a);
        return;

        if (WIFEXITED(status))
        {
            fprintf(stderr, "%s with PID %d exited normally\n", procbg[idx], a);
        }
        else
        {
            fprintf(stderr, "%s with PID %d exited abnormally\n", procbg[idx], a);
        }
    }

    return;
}

int main(int argc, char *argv[])
{

    // signal(SIGTSTP, SIG_IGN);
    // signal(SIGINT, SIG_IGN);
    // signal(SIGCHLD, bgprocprint);

    myid = getpid();
    for (int i = 1; i < 50; i++)
        bgpid[i] = -1;

    // to clear the terminal
    printf("\033[H\033[J");

    // print the welcome quote
    printf(BLUE "Welcome to " CYAN "Y.K. " BLUE "terminal\n\n");

    // to get the current path till the dollar sign
    char current_path[200];
    getcwd(current_path, 200);

    // printf("%s\n", current_path);

    // directory to work in
    int n = strlen(argv[0]);
    for (int i = n - 1; i >= 0; i--)
    {
        if (argv[0][i] == '/')
        {
            argv[0][i] = '\0';
            break;
        }
    }

    // make the home directory
    chdir(argv[0]);

    getcwd(home, 200);

    // printf("%s\n", current_path);
    chdir(current_path);

    while (1)
    {
        doneflag = 0;
        overwriteflag = 0;
        readflag = 0;
        appendflag = 0;

        // SIGNAL HANDLING
        // printf("here\n");
        signal(SIGTSTP, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        signal(SIGCHLD, bgprocprint);

        // printf("inp is just before normal display is: %s\n" , inp);

        display(home, val, "no", "no");

        val = 0;

    begin:;

        // get the input_cmd as input
        char *tcomm = (char *)malloc(sizeof(char) * 100);
        size_t len = 0;

        char *s = (char *)malloc(sizeof(char) * 100);
        int yyt = inputread("call", current_path, home, "");

        // printf("ykprob is : %d", ykprob);
        if (yyt != 11)
            printf("\n");

        if (yyt == 7)
        {
            captain = 1;
            strcpy(steve, help1);
            // printf("::--> %s\n" , help1);
            // printf("inp is just before the complex display is: %s\n" , inp);
            display(home, -7, help1, "no");
            goto begin;
            // continue;
        }

        // if (yyt == 11)
        // {
        //     // printf("kjfsjbnfskbn");
        //     captain = 1;
        //     strcpy(steve, help1);
        //     // printf("::--> %s\n" , help1);
        //     // printf("inp is just before the complex display is: %s\n" , inp);
        //     // display(home, -7, help1, "no");
        //     goto begin;
        //     // continue;
        // }
        // printf("yyt is %d\n", yyt);
        // printf("here i am\n");

        strcpy(s, getinp);

        // printf("s is %s\n", s);
        // if(s[strlen(s)-1] == '/')
        // {
        //     // printf("s is %s\n", s); 
        //     s[strlen(s)-1] == '\0';
        //     // printf("yes\n");
        // }
        // getline(&tcomm, &len, stdin);

        // printf("tcomm is %s\n", tcomm);

        // fgets(s , len ,stdin);

        // checking s
        int tyyt = strlen(s);
        int put_his = 0;
        for (int i = 0; i < tyyt; i++)
        {
            if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
            {
                put_his = 1;
                break;
            }
        }

        if (put_his == 1)
        {
            char forhis[100];
            strcpy(forhis, s);
            int temper = strlen(forhis);
            for (int i = 0; i < temper; i++)
            {
                if (forhis[i] == '\n')
                {
                    forhis[i] = '\0';
                    break;
                }
            }
            add_command_to_history(forhis, home);
        }

        int temp = strlen(s);
        // temp = temp - 1;
        // s[temp] = '\0';

        // count the number of semicolons
        int colons = 0;
        for (int i = 0; i < temp; i++)
        {
            if (s[i] == ';')
                colons++;
        }

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

            // CHECK IF PIPE THERE OR NOT
            // ************************************************************
            int uytu = strlen(s);
            int flagt = 0;
            for (int i = 0; i < uytu; i++)
            {
                if (s[i] == '|')
                {
                    flagt = 1;
                    break;
                }
            }
            if (flagt == 1)
            {
                pipeing(s, "token", current_path, home);
                continue;
            }
            // ************************************************************

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
                strcpy(command[k], s);
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
                strcpy(command[k], s);
            }
            // printf("s is --> %s\n", s);

            // printf("command      is   --> %s\n", command[k]);

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
            // printf("--> %s", s);
            int rjflag = 0, sjflag = 0;
            int ykt = strlen(s);
            for (int j = 0; j < ykt - 1; j++)
            {
                if (s[j] == '-' && s[j + 1] == 'r')
                    rjflag = 1;
                else if (s[j] == '-' && s[j + 1] == 's')
                    sjflag = 1;
            }

            // printf("rjflag is %d\n" , rjflag);
            // printf("sjflag is %d\n" , sjflag);

            char jobscompare[15];
            for (int j = 0; j < 4; j++)
                jobscompare[j] = s[j];
            jobscompare[4] = '\0';
            char *jobsstr = "jobs";
            if (strcmp(jobscompare, jobsstr) == 0)
            {
                if (rjflag == 0 && sjflag == 1)
                    jobs("..", "..", 4);
                else if (rjflag == 1 && sjflag == 0)
                    jobs("..", "..", 5);
                else if (rjflag == 1 && sjflag == 1)
                    jobs("..", "..", 6);
                else if (rjflag == 0 && sjflag == 0)
                    jobs("..", "..", 7);

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
                val = execute(command[k], home);
                if (val == -1)
                    val = 0;
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
        free(tcomm);
        // s[0] = '\0';
    }

    return 0;
}