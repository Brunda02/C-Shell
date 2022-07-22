#include "headers.h"

void sendsig(char **tokens, int num)
{
    int b = 1;
    if (num != 3)
    {
        printf("Number of Arguments are not matching\n");
        return;
    }
    int jobnum = atoi(tokens[1]);
    int signal = atoi(tokens[2]);

    if (jobnum == 0 || signal == 0)
        printf("Incorrect arguments are given\n");
    else
    {
        for (int i = 0; i < 100; i++)
        {
            if (bru[i].iden == -1)
            {
            }
            else
            {
                //printf("%d %d %d %d\n",bru[i].iden,bru[i].pid,jobnum,signal);
                if (b == jobnum)
                {
                    int y = kill(bru[i].pid, signal);
                    //printf("Hello\n");
                    if (y < 0)
                    {
                        printf("Error in given signal\n");
                        return;
                    }
                    break;
                }
                b++;
            }
        }
        if (b != jobnum)
            printf("That job doesn't exist\n");
    }
}