#include "headers.h"

void replay2(char **tokens)
{
    
    pid_t pid = fork();
    
        if (pid > 0)
        {
            wait(NULL);
        }
        else if (pid < 0)
        {
            perror("Error:");
        }
        else
        {
            //printf("%d %d %d\n",quotient, period,interval);
            // for (int i = 0; i < quotient; i++)
            // {
            // printf("%d\n",i);
            // sleep(interval);
            int m = execvp(tokens[0], tokens);
            if (m < 0)
            {
                perror("Error:");
                return;
            }
            //}
        }
    
}

void replay(char** tokens, int num)
{
    int period;
    int interval;
    if (num >= 5)
    {
        period = atoi(tokens[num - 1]);
        interval = atoi(tokens[num - 3]);
    }
    else
    {
        printf("Error\n");
        return;
    }
    if (period == 0 || interval == 0)
    {
        printf("Error\n");
        return;
    }
    char *cmd = strdup(tokens[2]);
    char *argv[num - 5];
    int j = 0;
    for (int i = 2; i < num - 4; i++)
    {
        //fprintf(stderr, "--%d--\n", bg);
        argv[j] = strdup(tokens[i]);
        j++;
    }
    argv[num - 5] = NULL;
    int quotient = period / interval;
    int remainder = period % interval;

    for(int i=0;i<quotient;i++){
        sleep(interval);
        replay2(argv);
    }
    if(remainder!=0) sleep(remainder);
}