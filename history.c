#include "main.h"

static char *storage[20];
static int hiscounter = 0;

void add_command_to_history(const char *command, char *home)
{
    if (command[0] == ' ' || command[0] == '\t' || command[0] == '\n')
        return;

    char help[250];
    strcpy(help, home);
    strcat(help, "/data.txt");
    // printf("help is %s\n\n" , help);

    char *buff;
    size_t line_buf_size;
    FILE *file = fopen(help, "r+");
    int jk = 0;
    while (getline(&buff, &line_buf_size, file) != -1)
    {
        // printf("buff is %s\n", buff);
        int temp = strlen(buff);
        buff[temp - 1] = '\0';
        storage[jk] = strdup(buff);
        jk++;
    }
    fclose(file);
    FILE *file1 = fopen(help, "w+");
    hiscounter = jk;
    // for (int index = 0; index <= jk; index++)
    // {
    //     printf("---> %s", storage[index]);
    // }
    int check_flag=0;
    if (hiscounter > 0)
    {
        if (strcmp(storage[hiscounter - 1], command) == 0)
            return;
    }
    // printf("prev is %s\n", storage[hiscounter - 1]);
    if (hiscounter < 20)
    {
        storage[hiscounter] = strdup(command);
        hiscounter += 1;
    }
    else
    {
        check_flag = 1;
        for (int index = 1; index < 20; index++)
        {
            storage[index - 1] = storage[index];
        }
    }

    if(check_flag == 1)
    {
        storage[19] = strdup(command);
    }

    for (int index = 0; index < hiscounter; index++)
    {
        fprintf(file1, "%s\n", storage[index]);
    }
    fclose(file1);
}

void print_history(char *home)
{
    char help[250];
    strcpy(help, home);
    strcat(help, "/data.txt");
    // printf("home is %s\n\n" , home);
    char *aarrprint[25];

    char *buff;
    size_t line_buf_size;
    FILE *file = fopen(help, "r");
    int arguments = 0;
    while (getline(&buff, &line_buf_size, file) != -1)
    {
        aarrprint[arguments] = strdup(buff);
        arguments++;
    }
    fclose(file);

    if (arguments < 10)
    {
        FILE *fptr;
        char c;
        fptr = fopen(help, "r");
        c = fgetc(fptr);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(fptr);
        }
        fclose(fptr);
    }
    else
    {
        for (int index = arguments - 10; index < arguments; index++)
        {
            printf("%s", aarrprint[index]);
        }
    }
}
