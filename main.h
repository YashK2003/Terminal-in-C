#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>
#include <ncurses.h>
#include <assert.h>
#include <fcntl.h>

int bgpid[500];
char *procbg[300];
extern char infile[200];
extern char outfile[200];
extern int readflag, overwriteflag, appendflag;
extern char joincom[200];
extern char getinp[300];
extern char help1[300];

extern int captain;
extern int directflag;
extern char steve[300];



char tomcr[200];
char inp[100];


int inputread(char *call, char *path, char *home , char *extra1);
int runstore(char *path, char *call, char *home);
void executecmds(char *call, char *current_path, char *home, int flag);
void pipeing(char *str, char *token, char *current_path, char *home);
void bgtofg(char *str);
void sigkill(int jobno, int signo);
void bgbtobgf(char *str);
void jobs(char *call1, char *call2, int token);
void redirection(char *str);
int execute(char *str, char *home);
void bgfinal(char *str, char *home);
void fgbgcall(char * str , char *home);
void bgcmd(char *str, char *home , char *bond[100]);
void display(char *home, int specflag ,char *extrapr1 ,char *extrapr2);
int fg(char *str, char *home);
void cd(char *path, char *home);
void echocmd(char *str);
void pwdcmd();
void ls(char *str, char *home);
void lscmd1(char *para1, char *para2, int flag);
void filnamewithl(int flag, char *para);
void pinfo(char *token, char *home);
void add_command_to_history(const char *command, char *home);
void print_history(char *home);
void show_dir_content(char *path, char *call, char *home);
void splitls(char *str, char *home);
void yash(int length, char *path);
void direcls(int flag, char *para);
void lsa(int flag);