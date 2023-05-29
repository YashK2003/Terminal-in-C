#include "main.h"

void pwdcmd()
{
    char cur_wrk_dir[300];
    getcwd(cur_wrk_dir, 300);

    printf("%s\n", cur_wrk_dir);
}