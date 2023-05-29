#include "main.h"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

void direcls(int flag, char *para)
{

    struct dirent **namelist;
    int n;
    n = scandir(para, &namelist, NULL, alphasort);
    if (n < 0)
    {
        perror("scandir");
        return;
    }
    char temp_path[200];
    getcwd(temp_path, 200);

    struct stat sb;
    int total = 0, i = 0;
    for (int i = 0; i < n; i++)
    {
        char *current_name = namelist[i]->d_name;

        char current_path[500];

        strcpy(current_path, temp_path);
        strcat(current_path, "/");
        strcat(current_path, current_name);

        stat(current_path, &sb);

        if (flag == 1 || (flag == 0 && current_name[0] != '.'))
            total += sb.st_blocks;
    }
    printf("total %d\n", total / 2);

    struct dirent *ent;
    struct tm *t;
    char print_date[500];

    i = 0;
    while (i < n)
    {
        char *current_name = namelist[i]->d_name;

        char current_path[500];

        strcpy(current_path, temp_path);
        strcat(current_path, "/");
        strcat(current_path, current_name);

        stat(current_path, &sb);

        if (flag == 1 || (flag == 0 && current_name[0] != '.'))
        {

            char ffty = '-';

            if (S_ISDIR(sb.st_mode))
                ffty = 'd';
            else if (S_ISCHR(sb.st_mode))
                ffty = 'c';
            else if (S_ISBLK(sb.st_mode))
                ffty = 'b';
            else if (S_ISREG(sb.st_mode))
                ffty = '-';
            else if (S_ISLNK(sb.st_mode))
                ffty = 'l';
            else if (S_ISSOCK(sb.st_mode))
                ffty = 's';
            else if (S_ISFIFO(sb.st_mode))
                ffty = 'f';

            printf("%c", ffty);

            printf((sb.st_mode & S_IRUSR) ? "r" : "-");
            printf((sb.st_mode & S_IWUSR) ? "w" : "-");
            printf((sb.st_mode & S_IXUSR) ? "x" : "-");
            printf((sb.st_mode & S_IRGRP) ? "r" : "-");
            printf((sb.st_mode & S_IWGRP) ? "w" : "-");
            printf((sb.st_mode & S_IXGRP) ? "x" : "-");
            printf((sb.st_mode & S_IROTH) ? "r" : "-");
            printf((sb.st_mode & S_IWOTH) ? "w" : "-");
            printf((sb.st_mode & S_IXOTH) ? "x" : "-");

            // print stuff
            printf("%d", (int)sb.st_nlink);

            printf(" %s", getpwuid(sb.st_uid)->pw_name);

            printf(" %s", getgrgid(sb.st_gid)->gr_name);

            printf(" %6ld", sb.st_size);

            t = localtime(&sb.st_mtime);
            strftime(print_date, 500, nl_langinfo(D_T_FMT), t);

            for (int i = 4; i < 16; i++)
            {
                print_date[i - 4] = print_date[i];
            }
            print_date[12] = '\0';

            printf(" %s ", print_date);

            struct stat st_buf;
            stat(current_name, &st_buf);

            // print the file
            if (S_ISDIR(st_buf.st_mode))
                printf(BLUE "%s \n" RESET, current_name);
            else if ((st_buf.st_mode & S_IXUSR))
                printf(GREEN "%s \n" RESET, current_name);
            else
                printf("%s \n", current_name);
            // printf("%s\n", current_name);
        }
        i++;
    }

    return;
}

void lsa(int flag)
{
    struct dirent **namelist;
    int n;
    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0)
    {
        perror("scandir");
        return;
    }
    char temp_path[200];
    getcwd(temp_path, 200);

    // TOTAL IMPLEMENTATION
    struct stat sb;
    long long int total = 0, i = 0;
    for (int i = 0; i < n; i++)
    {
        char *current_name = namelist[i]->d_name;

        char current_path[500];

        strcpy(current_path, temp_path);
        strcat(current_path, "/");
        strcat(current_path, current_name);

        stat(current_path, &sb);

        if (flag == 1 || (flag == 0 && current_name[0] != '.'))
            total += sb.st_blocks;
    }
    printf("total %lld\n", total / 2);

    // PRINT INFO
    struct dirent *ent;
    struct tm *t;
    char print_date[500];

    i = 0;
    while (i < n)
    {
        char *current_name = namelist[i]->d_name;

        char current_path[500];

        strcpy(current_path, temp_path);
        strcat(current_path, "/");
        strcat(current_path, current_name);

        stat(current_path, &sb);

        if (flag == 1 || (flag == 0 && current_name[0] != '.'))
        {
            // total+=sb.st_blocks;

            char ffty = '-';

            if (S_ISDIR(sb.st_mode))
                ffty = 'd';
            else if (S_ISCHR(sb.st_mode))
                ffty = 'c';
            else if (S_ISBLK(sb.st_mode))
                ffty = 'b';
            else if (S_ISREG(sb.st_mode))
                ffty = '-';
            else if (S_ISLNK(sb.st_mode))
                ffty = 'l';
            else if (S_ISSOCK(sb.st_mode))
                ffty = 's';
            else if (S_ISFIFO(sb.st_mode))
                ffty = 'f';

            printf("%c", ffty);

            printf((sb.st_mode & S_IRUSR) ? "r" : "-");
            printf((sb.st_mode & S_IWUSR) ? "w" : "-");
            printf((sb.st_mode & S_IXUSR) ? "x" : "-");
            printf((sb.st_mode & S_IRGRP) ? "r" : "-");
            printf((sb.st_mode & S_IWGRP) ? "w" : "-");
            printf((sb.st_mode & S_IXGRP) ? "x" : "-");
            printf((sb.st_mode & S_IROTH) ? "r" : "-");
            printf((sb.st_mode & S_IWOTH) ? "w" : "-");
            printf((sb.st_mode & S_IXOTH) ? "x" : "-");
            // print stuff
            printf(" %d", (int)sb.st_nlink);

            printf(" %s", getpwuid(sb.st_uid)->pw_name);

            printf(" %s", getgrgid(sb.st_gid)->gr_name);

            printf(" %6ld", sb.st_size);

            t = localtime(&sb.st_mtime);
            strftime(print_date, 500, nl_langinfo(D_T_FMT), t);

            for (int i = 4; i < 16; i++)
            {
                print_date[i - 4] = print_date[i];
            }
            print_date[12] = '\0';

            printf(" %s ", print_date);
            struct stat st_buf;
            stat(current_name, &st_buf);

            // print the file
            if (S_ISDIR(st_buf.st_mode))
                printf(BLUE "%s \n" RESET, current_name);
            else if ((st_buf.st_mode & S_IXUSR))
                printf(GREEN "%s \n" RESET, current_name);
            else
                printf("%s \n", current_name);
            // printf("%s\n", current_name);
        }
        i++;
    }
}

void lscmd1(char *para1, char *para2, int flag)
{
    // para 1 contains -a
    char test[100];
    getcwd(test, 100);

    if (chdir(para2) < 0)
    {
        printf("cd: %s: No such file or directory\n", para2);
        return;
    }

    struct dirent **namelist;
    int n;
    int i = 0;
    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {

        for (int i = 0; i < n; i++)
        {
            if (flag == 5)
            {
                struct stat st_buf;
                stat(namelist[i]->d_name, &st_buf);

                if (S_ISDIR(st_buf.st_mode))
                    printf(BLUE "%s " RESET, namelist[i]->d_name);
                else if ((st_buf.st_mode & S_IXUSR))
                    printf(GREEN "%s " RESET, namelist[i]->d_name);
                else
                    printf("%s ", namelist[i]->d_name);

                free(namelist[i]);
            }

            if (flag == 7)
            {
                if ((namelist[i]->d_name)[0] != '.')
                {
                    struct stat st_buf;
                    stat(namelist[i]->d_name, &st_buf);

                    if (S_ISDIR(st_buf.st_mode))
                        printf(BLUE "%s " RESET, namelist[i]->d_name);
                    else if ((st_buf.st_mode & S_IXUSR))
                        printf(GREEN "%s " RESET, namelist[i]->d_name);
                    else
                        printf("%s ", namelist[i]->d_name);
                }
                // printf("%s ", namelist[i]->d_name);
                free(namelist[i]);
            }
        }
        printf("\n");
        free(namelist);
    }

    chdir(test);
    return;
}

void yash(int length, char *path)
{

    // PRINT INFO
    struct stat sb;
    struct dirent *ent;
    struct tm *t;
    char print_date[500];

    stat(path, &sb);

    // total+=sb.st_blocks;

    char ffty = '-';

    if (S_ISDIR(sb.st_mode))
        ffty = 'd';
    else if (S_ISCHR(sb.st_mode))
        ffty = 'c';
    else if (S_ISBLK(sb.st_mode))
        ffty = 'b';
    else if (S_ISREG(sb.st_mode))
        ffty = '-';
    else if (S_ISLNK(sb.st_mode))
        ffty = 'l';
    else if (S_ISSOCK(sb.st_mode))
        ffty = 's';
    else if (S_ISFIFO(sb.st_mode))
        ffty = 'f';

    printf("%c", ffty);

    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %d", (int)sb.st_nlink);

    printf(" %s", getpwuid(sb.st_uid)->pw_name);
    
    printf(" %s", getgrgid(sb.st_gid)->gr_name);
    
    printf(" %6ld", sb.st_size);

    t = localtime(&sb.st_mtime);
    strftime(print_date, 500, nl_langinfo(D_T_FMT), t);

    for (int i = 4; i < 16; i++)
    {
        print_date[i - 4] = print_date[i];
    }
    print_date[12] = '\0';

    printf(" %s ", print_date);
    struct stat st_buf;
    stat(path, &st_buf);

    // print the file
    if (S_ISDIR(st_buf.st_mode))
        printf(BLUE "%s \n" RESET, path + length);
    else if ((st_buf.st_mode & S_IXUSR))
        printf(GREEN "%s \n" RESET, path + length);
    else
        printf("%s \n", path + length);
    // printf("%s\n", current_name);
    // printf(" %s %s\n", print_date, path + length);
}

void splitls(char *str, char *home)
{
    // printf("%ld\n",strlen(str));
    if (strlen(str) != 2)
    {
        if (str[2] != ' ' && str[2] != '\t' && str[2] != '\n')
        {
            printf("Invalid command\n");
            return;
        }
    }

    str = strtok(str, " \t");
    // printf("%s\n",str);

    char bond[100][100];
    int lflag = 0;
    int aflag = 0;

    int laflag = 0;
    int tildaflag = 0;

    int count = 1;
    while (1)
    {
        str = strtok(NULL, " \t");

        if (str == NULL)
        {
            break;
        }

        if (strcmp(str, "-l") == 0)
        {
            lflag = 1;
            continue;
        }

        if (strcmp(str, "-a") == 0)
        {
            aflag = 1;
            continue;
        }

        if (strcmp(str, "~") == 0)
        {
            tildaflag = 1;
            continue;
        }

        if (strcmp(str, "-al") == 0 || strcmp(str, "-la") == 0)
        {
            laflag = 1;
            continue;
        }

        strcpy(bond[count], str);
        // printf("%d. %s\n", count, str);
        count++;
    }

    // NOW HANDLE THE NEW CASES
    // // LS Tilda
    // if (count == 1 && tildaflag == 0)
    // {
    //     lscmd1("aa", home, 7);
    //     return;
    // }

    //  LS command
    if (count == 1 && aflag == 0 && lflag == 0 && laflag == 0)
        lscmd1("aa", ".", 7);

    // LS -l
    if (count == 1 && aflag == 0 && lflag == 1 && laflag == 0)
        lsa(0);

    // LS -a
    if (count == 1 && aflag == 1 && lflag == 0 && laflag == 0)
        lscmd1("aa", ".", 5);

    // LS -l -a and LS -al and LS -la
    if ((count == 1 && aflag == 1 && lflag == 1) || (count == 1 && laflag == 1))
        lsa(1);

    //  NOW CALL FOR LS
    for (int i = 1; i < count; i++)
    {

        int status;
        struct stat st_buf;
        status = stat(bond[i], &st_buf);
        if (status != 0)
        {
            printf("ls: cannot access '%s': No such file or directory\n", bond[i]);
            continue;
        }

        // IF IT IS FILE THEN DO THIS
        if (S_ISREG(st_buf.st_mode))
        {
            if (lflag == 0 && aflag == 0)
            {
                printf("%s\n", bond[i]);
            }

            if (lflag == 1 && aflag == 0)
            {
                if (bond[i][0] == '/')
                {
                    yash(0, bond[i]);
                    continue;
                }
                char para[250];
                getcwd(para, 250);
                int len = strlen(para);
                strcat(para, "/");
                strcat(para, bond[i]);
                yash(len, para);
            }
        }
        if (S_ISDIR(st_buf.st_mode))
        {
            if (laflag == 1)
            {
                if (bond[i][0] == '/')
                {
                    direcls(1, bond[i]);
                    continue;
                }

                char para[250];
                getcwd(para, 250);
                int len = strlen(para);
                strcat(para, "/");
                strcat(para, bond[i]);
                // printf("%s\n", para);
                direcls(1, para);
                continue;
            }

            if (lflag == 0 && aflag == 0)
            {
                lscmd1("aa", bond[i], 7);
            }

            if (lflag == 1 && aflag == 0)
            {
                if (bond[i][0] == '/')
                {
                    direcls(0, bond[i]);
                    continue;
                }
                char para[250];
                getcwd(para, 250);
                int len = strlen(para);
                strcat(para, "/");
                strcat(para, bond[i]);
                // printf("%s\n", para);
                direcls(0, para);
            }

            if (lflag == 0 && aflag == 1)
            {
                lscmd1("aa", bond[i], 5);
            }

            if (lflag == 1 && aflag == 1)
            {
                if (bond[i][0] == '/')
                {
                    direcls(1, bond[i]);
                    continue;
                }

                char para[250];
                getcwd(para, 250);
                int len = strlen(para);
                strcat(para, "/");
                strcat(para, bond[i]);
                // printf("%s\n", para);
                direcls(1, para);
            }
        }
    }
}