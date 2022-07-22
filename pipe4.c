#include "headers.h"

int TerminalOutput;
int TerminalInput;

void foreground2(char *tokens[], int num, int* pipe, int prev)
{
    
    
    int pid = fork();
    if (pid == 0)
    {
        
        if (pipe != NULL)
        {
            close(pipe[1]); 
            close(pipe[0]); 
        }
        setpgid(0, 0);
        int m = execvp(tokens[0], tokens);
        if (m == -1)
        {
            printf("Error\n");
            return;
        }
    }
    else if (pid > 0)
    {
        if (pipe != NULL)
        {
            close(pipe[1]);
            if (prev != -1)
                close(prev);
        }
        if (prev != -1)
                close(prev);
        wait(NULL);
    }
    else 
    {
        printf("Error in forking\n");
        return;
    }
}

char *formatinput2(char *str)
{
    char str1[2] = "|";
    char str2[2] = "<";
    char str3[2] = ">";
    char str4[3] = ">>";

    char *changedstr;
    changedstr = (char *)malloc(sizeof(char) * 250);
    changedstr[0] = ' ';
    int l = strlen(str);
    int b = 1, i;
    for (i = 0; i < l - 1; i++)
    {
        if (str[i] == str1[0] || str[i] == str2[0] || (str[i] == str3[0] && str[i + 1] != str3[0]))
        {
            changedstr[b] = ' ';
            b++;
            changedstr[b] = str[i];
            b++;
            changedstr[b] = ' ';
            b++;
        }
        else if ((str[i] == str3[0] && str[i + 1] == str3[0]))
        {
            changedstr[b] = ' ';
            b++;
            changedstr[b] = str[i];
            b++;
            changedstr[b] = str[i + 1];
            b++;
            changedstr[b] = ' ';
            b++;
            i++;
        }
        else
        {
            changedstr[b] = str[i];
            b++;
        }
    }
    if (i == (l - 1))
        changedstr[b] = str[i];
    //printf("%s\n",str);
    // printf("%s\n",changedstr);
    return changedstr;
}

//each redirection
void redirection(char *sym, char *file)
{
    int f;
    if (strcmp(sym, ">") == 0) //input
    {
        f = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
        if (f < 0)
        {
            printf("Error\n");
        }
        else
        {
            dup2(f, 1);
            close(f);
        }
    }
    if (strcmp(sym, ">>") == 0)
    {
        f = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
        if (f < 0)
            printf("Error\n");
        else
        {
            dup2(f, 1);
            close(f);
        }
    }
    if (strcmp(sym, "<") == 0)
    {
        f = open(file, O_RDWR);
        if (f < 0)
            printf("Error\n");
        else
        {
            dup2(f, 0);
            close(f);
        }
    }
}

void gen_redirection(char *str, int* arr, int prev)
{
    char *str2[50];
    for (int i = 0; i < 50; i++)
    {
        str2[i] = (char *)malloc(100 * sizeof(char));
    }
    char **arguments;
    int k = 0, i;
    char *tokenized;
    arguments = calloc(1, sizeof(char *));
    tokenized = strtok(str, "\t ");
    while (tokenized != NULL)
    {
        arguments[k] = tokenized;
        ++k;
        arguments = realloc(arguments, sizeof(char *) * (k + 1));
        tokenized = strtok(NULL, "\t ");
    }
    arguments[k] = NULL;
    // printf("%d\n",k);               /////////////////////
    for (i = 0; i < k - 1; i++)
    {
        if (strcmp(arguments[i], "<") == 0 || strcmp(arguments[i], ">") == 0 || strcmp(arguments[i], ">>") == 0)
        {
            // printf("Hello\n");
            redirection(arguments[i], arguments[i + 1]);
            //printf("Hello\n");
        }
    }
    // printf("Hello\n");                  //////////////////
    if (strcmp(arguments[k - 1], "<") == 0 || strcmp(arguments[k - 1], ">") == 0 || strcmp(arguments[k - 1], ">>") == 0)
    {
        return;
    }
    //  printf("Hello\n");               ////////////////////
    int l = 0;
    for (i = 0; i < k - 1; i++)
    {
        if (strcmp(arguments[i], "<") == 0 || strcmp(arguments[i], ">") == 0 || strcmp(arguments[i], ">>") == 0)
        {
            // i++;
            // printf("Hello\n");
            break;
        }
        // printf("Hello\n");
        strcpy(str2[l], arguments[i]);
        l++;
    }
    if (i == k - 1)
    {
        strcpy(str2[l], arguments[k - 1]);
        l++;
    }
    //printf("Hello\n");
    str2[l] = NULL;
    //printf("%d\n", l);
    foreground2(str2,l,arr,prev);
    //printf("Hello\n");
}

void checkpipe(char *str)
{
    char **cmds;
    int k = 0;
    char *token;
    cmds = calloc(1, sizeof(char *));
    token = strtok(str, "|");
    TerminalOutput = dup(1);
    TerminalInput = dup(0);
    while (token != NULL)
    {
        cmds[k] = token;
        ++k;
        cmds = realloc(cmds, sizeof(char *) * (k + 1));
        token = strtok(NULL, "|");
    }
    cmds[k] = NULL;
    if (k == 1)
    {
        // printf("Hello\n");
        gen_redirection(str,NULL,-1);
        // printf("Hello\n");
    }
    else
    {
        // printf("Hello\n");
        if (str[0] == '|' || str[strlen(str) - 1] == '|')
        {
            printf("Pipes at beginning or end of statement not possible");
            return;
        }
        int k1 = 0;
        int prev = -1;
        while (k1 < k - 1)
        {
            int m;
            int arr[2];
            m = pipe(arr);
            if (m < 0)
            {
                printf("Error\n");
            }
            if (prev != -1)
            {
                dup2(prev, 0);
                close(prev);
            }
            dup2(arr[1], 1);
            close(arr[1]);
            gen_redirection(cmds[k1],arr,prev);
            prev = arr[0];
            // dup2(arr[0], 0);
            // close(arr[0]);
            k1++;
        }
        dup2(TerminalOutput, 1);
        close(TerminalOutput);
        //  dup2(out2, 1);
        //  close(out2);
        if (prev != -1)
        {
            dup2(prev, 0);
            close(prev);
        }
        gen_redirection(cmds[k - 1],NULL,prev);
        dup2(TerminalInput, 0);
        close(TerminalInput);
    }
    dup2(TerminalInput, 0);
    close(TerminalInput);
    dup2(TerminalOutput, 1);
    close(TerminalOutput);
    dup2(out2,1);
    close(out2);
}

void genbru(char *str)
{
    //printf("%s\n", str);
    char *chstr;
    chstr = formatinput2(str);
    checkpipe(chstr);
    dup2(out, 1);
    close(out);
}