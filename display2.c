#include "headers.h"
#include "input.c"
//int zeb =0;

char *display()
{
    char systemname[250];
    char owner[250];
    if (getlogin_r(owner, 250) == 0)
    {
    }
    else
        printf("Owner is not found\n");
    if (gethostname(systemname, 250) == 0)
    {
    }
    else
        printf("Systemname is not found");
    char *x = (char *)malloc(502 * sizeof(char));
    strcpy(x, owner);
    strcat(x, "@");
    strcat(x, systemname);
    strcat(x, ":");

    return x;
}

void ctrlc(int sig_num)
{
    if (fore.pid != -1)
    {
        if (kill(fore.pid, 9) == 0)
            fore.pid = -1;
        return;
    }
    else
    {
        printf("\n%s%s", mainline, reldir);
        signal(SIGINT, ctrlc);
        fflush(stdout);
    }
}

void ctrlz(int sig_num)
{
    zeb = 0;
   // printf("%d\n", fore.pid);
    if (fore.pid != -1)
    {
        //printf("Hello\n");
        //printf("%d\n",fore.pid);
        if (kill(fore.pid, SIGTSTP) == 0)
        {
            //kill(bid,SIGTSTP);
            //fore.pid = -1;
            totalbackground++;
            bru[totalbackground].pid = fore.pid;
            //printf("Hell0\n");
            bru[totalbackground].name = (char *)malloc(50 * sizeof(char));
            strcpy(bru[totalbackground].name, fore.name);
            //printf("Hell0\n");
            bru[totalbackground].iden = 1;
            //printf("%s %d %d %d\n",bru[totalbackground].name,bru[totalbackground].iden,bru[totalbackground].pid, totalbackground);
            fore.pid = -1;
            //printf("\n%s%s", mainline,reldir);
            //kill(fore.pid,SIGSTOP);
            //printf("Hello\n");
            return;
        }
    }
    else
    {
        //printf("Hello\n");
        printf("\n%s%s", mainline, reldir);
        signal(SIGSTOP, ctrlz);
        fflush(stdout);
    }
}

int main()
{
    out = dup(1);
    out2=dup(STDOUT_FILENO);
    char input[500];
    int b;
    printf("\033[H\033[J");
    printf("\e[3J");
    printf("<-----------------Welcome to my shell-------------->\n");
    mainline = display();
    if (getcwd(homedir, 250))
    {
    }
    else
        printf("Absolute address of home directory is not obtained\n");
    strcpy(currdir, homedir);
    strcpy(reldir, "~$ ");
    printf("%s", mainline);
    printf("~$ ");
    bid = getpid();
    for (int i = 0; i < 100; i++)
    {
        bru[i].iden = -1;
    }
    //signal(SIGCHLD,child);
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    //signal(SIGSTOP, ctrlz);
    while (1)
    {
        fore.pid = -1;
        zeb = 0;
        int end;
        //   signal(SIGINT, ctrlc);
        //   signal(SIGTSTP, ctrlz);
        end = gets(input);
        if (end == 0)
        {
            //printf("Hello\n");
            //kill(bid,9);
            if (kill(bid, 9) == 0)
            {
            }
        }
        if (b)
            hel();
        history(input, strlen(input), homedir);
        formatinput(input);
        dup2(out2,STDOUT_FILENO);
        close(out2);
        printf("%s%s", mainline, reldir);
        b = 1;
    }
}