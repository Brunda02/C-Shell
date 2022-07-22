#include "headers.h"

void processdelete(int pid)
{
   int i;
   for(i=0;i<100;i++)
   {
     if(bru[i].pid==pid) bru[i].iden=-1;
   }
}

void fg(char** tokens, int num)
{
    int index, i;
    int cntr = 1;
    if (num == 2)
    {
       index = atoi(tokens[1]);
        for (i = 0; i < 100; i++)
        {
            if (bru[i].iden == -1)
            {
                continue;
            }
            if (cntr == index)
            {
             signal(SIGTTIN, SIG_IGN);
             signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(0,bru[i].pid);
            fore.pid=bru[i].pid;
            fore.name = (char*) malloc(50*sizeof(char));
            strcpy(fore.name,bru[i].name);
            kill(bru[i].pid, SIGCONT);
            //processdelete(bru[i].pid);  
            waitpid(-1, NULL, WUNTRACED); 
            tcsetpgrp(0,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
            fore.pid=bru[i].pid;
            break;
            }
            cntr++;
        }
        if (index != cntr || (index==1 && cntr==1))
            printf(" No such job is found\n"); 
    }
    else
    {
        printf("No proper arguments\n");
    }
}

void bg(char **tokens, int num)
{
    int index, i;
    int cntr = 1;
    if (num == 2)
    {
        index = atoi(tokens[1]);
        for (i = 0; i < 100; i++)
        {
            if (bru[i].iden == -1)
            {
                continue;
            }
            if (cntr == index)
            {
                kill(bru[i].pid, SIGTTIN);
                kill(bru[i].pid, SIGCONT);
                break;
            }
            cntr++;
        }
        if (index != cntr)
            printf("Error: No such job found\n");
    }
    else
    {
        printf("No proper arguments\n");
    }
}