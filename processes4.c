#include "headers.h"
#include "processes3.c"

void foreground(char **tokens)
{
    pid_t pid;
    int status;
    pid = fork();

    if (pid < 0)
        printf("Error\n");
    else if (pid > 0)
    {
        fore.pid=pid;
        fore.name=(char*)malloc(50*sizeof(char));
        strcpy(fore.name,tokens[0]);
        // printf("Hello\n");
        //int b = waitpid(pid,&status,WNOHANG| WUNTRACED);
        waitpid(pid,&status,WUNTRACED);
        //pid = wait(NULL);
        // printf("Hello\n");
    }
    else
    {
       //setpgid(0, 0);
        int y = execvp(tokens[0], tokens);
        if (y == -1)
        {
            perror("Error");
            exit(1);
        }
    }
}

void background(char **tokens)
{
    char buff[10];
    pid_t pid;
    int *status;
    pid = fork();
    if (pid < 0)
        printf("Error\n");
    else if (pid > 0)
    {
        printf("(%d) \n", pid);
        bru[totalbackground].iden=1;
        bru[totalbackground].pid=pid;
        bru[totalbackground].name=(char*)malloc(50*sizeof(char));
        strcpy(bru[totalbackground].name,tokens[0]);
        totalbackground++;
        push(&head,pid,tokens[0]);
    }
    else
    {
        setpgid(0, 0);
        //execvp(tokens[0], tokens);
        int y = execvp(tokens[0], tokens);
        if (y == -1)
        {
            perror("Error");
            exit(1);
        }
    }
}

void check(char **tokens, int num)
{
    int bg = 0;
    for (int i = 0; i < num; i++)
    {
        if (strcmp(tokens[i], "&") == 0)
        {
            bg = 1;
            //printf("%d\n", bg);
            tokens[i] = '\0';
        }
    }
    if (bg == 1)
        background(tokens);
    else
        foreground(tokens);
}
