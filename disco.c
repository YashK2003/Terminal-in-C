#include "main.h"

#define NORMAL_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

char cutpart[250];
char direc[200];
char flogic[300];
int yt;

void discover(char *path, int flag, char *token)
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

            if (flag == 1 && strcmp(token, namelist[i]->d_name) == 0)
            {
                printf(".%s\n", d_path + yt);
                return;
            }

            stat(d_path, &st_buf);
            if (S_ISREG(st_buf.st_mode))
            {
                if (flag == 0)
                    printf(".%s\n", d_path + yt);
                else if (flag == 2)
                    printf(".%s\n", d_path + yt);
            }
            if (S_ISDIR(st_buf.st_mode))
            {
                if (namelist[i]->d_name[0] == '.')
                {
                    i++;
                    continue;
                }
                if (flag == 0 || flag == 3)
                    printf(".%s\n", d_path + yt);
                discover(d_path, flag, token);
                // printf("bvjwv\n");
            }

            i++;
        }
        // free(namelist[i]);
    }
}

void show_dir_content(char *path, char *call, char *home)
{
    // getcwd(flogic, 200);
    // yt = strlen(flogic);
    // discover(path, 0, 0, 0);
    // return;

    char target_dir[250];
    char flags[250];
    char filename[250];
    // printf("after call1 is %s\n", call);

    int dflag = 0, fflag = 0, dotflag = 0, ddot2flag = 0, tildafla = 0;
    int direcnameflag = 0, filenameflag = 0;

    call = strtok(call, " \t");

    while (1)
    {
        if (call == NULL)
        {
            break;
        }
        if (call != NULL)
            call = strtok(NULL, " \t");

        if (call != NULL)
        {
            if (strcmp(call, "-d") == 0)
                dflag = 1;
            else if (strcmp(call, "~") == 0)
                tildafla = 1;
            else if (strcmp(call, "-f") == 0)
                fflag = 1;
            else if (call[0] == '"')
            {
                // printf("in here is %s\n\n", call);
                int lent = strlen(call);
                for (int i = 1; i < lent - 1; i++)
                {
                    filename[i - 1] = call[i];
                }
                filename[lent - 2] = '\0';

                filenameflag = 1;
                // printf("in here is %s\n\n", filename);
            }
            else if (call[0] == '~')
            {
                direcnameflag = 1;
                tildafla = 1;
            }
            else if (call[0] != '"' && call[0] != ' ')
            {
                strcpy(target_dir, call);
                direcnameflag = 1;
            }
        }

        // printf("%s\n", call);
    }

    /*if (call != NULL)
    {
        if (strcmp(target_dir, ".") == 0)
            dotflag = 1;
        else if (strcmp(target_dir, "..") == 0)
            ddot2flag = 1;
        else if (strcmp(target_dir, "-d") == 0)
            dflag = 1;
        else if (strcmp(target_dir, "-f") == 0)
            fflag = 1;
        else if (strcmp(target_dir, "~") == 0)
            tildafla = 1;
        else
        {
            strcpy(target_dir, call);
            direcnameflag = 1;
        }
    }

    if (call != NULL)
        call = strtok(NULL, " \t");
    if (call != NULL)
    {

        if (strcmp(flags, "-f") == 0)
            fflag = 1;
        else if (strcmp(flags, "-d") == 0)
            dflag = 1;
        else if (strcmp(flags, "") != 0)
        {
            filenameflag = 1;
            strcpy(flags, call);
        }
    }

    if (call != NULL)
        call = strtok(NULL, " \t");

    if (call != NULL)
    {
        if (strcmp(filename, "-f") == 0)
            fflag = 1;
        else if (strcmp(filename, "-d") == 0)
            dflag = 1;
        else if (strcmp(filename, "") != 0)
        {
            strcpy(filename, call);
            filenameflag = 1;
        }
    }*/

    // printf("dflag is %d\n", dflag);
    // printf("fflag is %d\n", fflag);
    // printf("dotflag is %d\n", dotflag);
    // printf("ddot2flag is %d\n", ddot2flag);
    // printf("tildafla is %d\n", tildafla);
    // printf("direcnameflag is %d\n", direcnameflag);
    // printf("filenameflag is %d\n", filenameflag);

    if (tildafla == 1)
        direcnameflag = 1;

    if (fflag == 0 && dflag == 0 && dotflag == 0 && ddot2flag == 0)
    {
        if (direcnameflag == 0 && tildafla == 0 && filenameflag == 0)
        {
            getcwd(flogic, 200);
            yt = strlen(flogic);
            printf(".\n");
            discover(path, 0, filename);
            return;
        }
    }

    if (filenameflag == 1)
    {
        if (direcnameflag == 1)
        {
            if (tildafla == 1)
            {
                // printf("%s\n", home);
                getcwd(flogic, 200);
                chdir(home);
                char parapass[200];
                getcwd(parapass, 200);
                yt = strlen(parapass);
                discover(parapass, 1, filename);
                chdir(flogic);
                return;
            }
            else
            {
                // printf("--> %s\n", target_dir);
                getcwd(flogic, 200);
                chdir(target_dir);
                char parapass[200];
                getcwd(parapass, 200);
                // printf("--> %s\n", parapass);
                yt = strlen(flogic);
                discover(parapass, 1, filename);
                chdir(flogic);
                return;
            }
        }
        else
        {
            if (tildafla == 1)
            {
                getcwd(flogic, 200);
                chdir(home);
                char parapass[200];
                getcwd(parapass, 200);
                yt = strlen(parapass);
                discover(parapass, 1, filename);
                chdir(flogic);
                return;
            }

            // printf("%s\n",filename);
            getcwd(flogic, 200);
            yt = strlen(flogic);
            discover(flogic, 1, filename);
            chdir(flogic);
            return;
        }
    }
    else
    {
        if (direcnameflag == 1)
        {
            if (tildafla == 1)
            {
                getcwd(flogic, 200);
                chdir(home);
                char parapass[200];
                getcwd(parapass, 200);
                yt = strlen(parapass);

                if ((dflag == 1 && fflag == 1) || (dflag == 0 && fflag == 0))
                {
                    discover(parapass, 0, filename);
                    chdir(flogic);
                    return;
                }
                else if (dflag == 0 && fflag == 1)
                {
                    discover(parapass, 2, filename);
                    chdir(flogic);
                    return;
                }
                else if (dflag == 1 && fflag == 0)
                {
                    discover(parapass, 3, filename);
                    chdir(flogic);
                    return;
                }

                // discover(parapass, 0, filename);
                chdir(flogic);
                return;
            }
            else
            {
                getcwd(flogic, 200);
                chdir(target_dir);
                char parapass[200];
                getcwd(parapass, 200);
                yt = strlen(flogic);
                if ((dflag == 1 && fflag == 1) || (dflag == 0 && fflag == 0))
                {
                    discover(parapass, 0, filename);
                    chdir(flogic);
                    return;
                }
                else if (dflag == 0 && fflag == 1)
                {
                    discover(parapass, 2, filename);
                    chdir(flogic);
                    return;
                }
                else if (dflag == 1 && fflag == 0)
                {
                    discover(parapass, 3, filename);
                    chdir(flogic);
                    return;
                }
                // discover(parapass, 0, filename);
                chdir(flogic);
                return;
            }
        }
        else
        {
            getcwd(flogic, 200);
            yt = strlen(flogic);
            if ((dflag == 1 && fflag == 1) || (dflag == 0 && fflag == 0))
            {
                discover(flogic, 0, filename);
                chdir(flogic);
                return;
            }
            else if (dflag == 0 && fflag == 1)
            {
                discover(flogic, 2, filename);
                chdir(flogic);
                return;
            }
            else if (dflag == 1 && fflag == 0)
            {
                discover(flogic, 3, filename);
                chdir(flogic);
                return;
            }
        }
    }

    /*if (dotflag == 1)
    {
        getcwd(flogic, 200);
        yt = strlen(flogic);

        if (dflag == 1 && direcnameflag == 0)
        {
            discover(path, 3, flags);
            return;
        }
        else if (fflag == 1 && direcnameflag == 0 && filenameflag == 0)
        {
            discover(path, 2, flags);
            return;
        }
        else if (direcnameflag == 0 && filenameflag == 1)
        {
            discover(path, 1, filename);
            return;
        }
        else
        {
            printf(".\n");
            discover(path, 0, filename);
            return;
        }
    }
    else if (ddot2flag == 1)
    {
        chdir(path);
        chdir("..");
        char topass[250];
        getcwd(topass, 250);
        chdir(path);
        if (dflag == 1 && direcnameflag == 0)
        {
            yt = strlen(topass);
            discover(topass, 3, flags);
            return;
        }
        else if (fflag == 1 && direcnameflag == 0)
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            discover(topass, 2, flags);
            return;
        }
        if (direcnameflag == 0 && filenameflag == 1)
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            discover(topass, 1, flags);
            return;
        }
        else
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            printf(".\n");
            discover(topass, 0, filename);
            return;
        }
    }
    else if (tildafla == 1)
    {
        chdir(home);
        char topass[250];
        getcwd(topass, 250);
        chdir(path);
        if (dflag == 1 && direcnameflag == 0)
        {
            // printf("vkjnvkr");
            // getcwd(flogic, 200);
            yt = strlen(topass);
            discover(topass, 3, flags);
            return;
        }
        else if (fflag == 1 && direcnameflag == 0)
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            discover(topass, 2, flags);
            return;
        }
        if (direcnameflag == 0 && filenameflag == 1)
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            // printf("~\n");
            discover(topass, 1, flags);
            return;
        }
        else
        {
            // getcwd(flogic, 200);
            yt = strlen(topass);
            discover(topass, 0, filename);
            return;
        }
    }
    else if (direcnameflag == 1)
    {

        char path_to_dir[250];
        strcpy(path_to_dir, path);
        strcat(path_to_dir, target_dir + 1);

        if (target_dir[0] == '~')
        {
            yt = strlen(home);
            strcpy(path_to_dir, home);
            strcat(path_to_dir, target_dir + 1);
        }
        else if (target_dir[0] == '/')
        {
            strcpy(path_to_dir, target_dir);
        }
        else if (target_dir[0] != '.')
        {
            yt = strlen(path);
            strcpy(path_to_dir, path);
            strcat(path_to_dir, "/");
            strcat(path_to_dir, target_dir);
        }

        // printf("--->   %s\n", path_to_dir);

        if (filenameflag == 0)
        {
            if ((dflag == 1 && fflag == 1) || (dflag == 0 && fflag == 0))
            {
                yt = strlen(path);
                discover(path_to_dir, 0, flags);
                return;
            }
            else if (dflag == 0 && fflag == 1)
            {
                yt = strlen(path);
                discover(path_to_dir, 2, flags);
                return;
            }
            else if (dflag == 1 && fflag == 0)
            {
                yt = strlen(path);
                discover(path_to_dir, 3, flags);
                return;
            }
        }
        else
        {
            if ((dflag == 1 && fflag == 1) || (dflag == 0 && fflag == 0))
            {
                // printf("--->   %s\n", path);
                discover(path_to_dir, 1, flags);
                return;
            }
            else if (dflag == 0 && fflag == 1)
            {
                discover(path_to_dir, 1, flags);
                return;
            }
            else if (dflag == 1 && fflag == 0)
            {
                printf(".\n");
                return;
            }
        }
    }

    if (direcnameflag == 0 && filenameflag == 0)
    {
        if (dflag == 1 && fflag == 0)
        {
            // printf("vkjnvkr");
            getcwd(flogic, 200);
            yt = strlen(flogic);
            discover(path, 3, flags);
            return;
        }
        else if (fflag == 1 && dflag == 0)
        {
            getcwd(flogic, 200);
            yt = strlen(flogic);
            discover(path, 2, flags);
            return;
        }
        else if (fflag == 1 && dflag == 1)
        {
            getcwd(flogic, 200);
            yt = strlen(flogic);
            discover(path, 0, flags);
            return;
        }
    }

    // printf("dflag is %d\n", dflag);
    // printf("fflag is %d\n", fflag);
    // printf("dotflag is %d\n", dotflag);
    // printf("ddot2flag is %d\n", ddot2flag);
    // printf("tildafla is %d\n", tildafla);
    // printf("direcnameflag is %d\n", direcnameflag);
    // printf("filenameflag is %d\n", filenameflag);

    // if (direcnameflag == 1)
    {
        // struct stat st_buf;

        // int status = stat(target_dir, &st_buf);
        // if (status != 0)
        // {
        //     printf("ls: cannot access '%s': No such file or directory\n", target_dir);
        //     return;
        // }

        char curdir[250];
        getcwd(curdir, 250);
        chdir(target_dir);

        char curdircall[250];
        getcwd(curdircall, 250);

        // if (dflag == 1)
        //     discover(curdircall, 3, 0, 0);
        // else if (fflag == 1)
        //     discover(curdircall, 2, 0, 0);
        // else

        getcwd(flogic, 300);
        // discover(curdircall, 3, 0, 0);

        chdir(curdir);

        return;
    }

    getcwd(cutpart, 250);
    yt = strlen(cutpart);
    // discover(path, 0, 0, 0);*/
}
