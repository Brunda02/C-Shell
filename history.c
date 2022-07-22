#include "headers.h"

void history(char* str, int num, char* homedir)
{

    char* line[30];
    int n = 0;
    FILE *f;
    char buffer[250];
    char path[250];
    strcpy(path,homedir);
    strcat(path,"/");
    strcat(path,"history.txt");
    f = fopen(path, "a");
    if (f != NULL)
    {
       // printf("%s\n",str);
        fputs(str, f);
        fputs("\n", f);
       // printf("%s\n",str);
        fclose(f);
    }
    FILE *f3 = fopen(path, "r");
    if (f3 != NULL)
    {
        while ((fgets(buffer, 250, f3)) != NULL)
        {
             line[n]=(char*)malloc(250*(sizeof(char)));
            strcpy(line[n], buffer);
             //printf("%s\n",buffer);
             // printf("%s\n",lines[n]);
            n++;
        }
      fclose(f3);
    }
    
    FILE* f2 = fopen(path, "w");
    if (f2 != NULL)
    {
        int maxi;
        if(n>=20) maxi=(n-20);
        else maxi=0;
        for (int i = maxi; i < n; i++)
        {
           // printf("%s %d\n", lines[i], i);
            fputs(line[i], f2);
            free(line[i]);
        }
        fclose(f2);
    }

}

void comhistory(int num)
{
    FILE *ptr;
    //char c;
    char buffer[250];
    int line = 0, i = 0;
    if ((ptr = fopen("history.txt", "r")) == NULL)
    {
        printf("Error locating desired file\n");
        exit(1);
    }
    else
    {
        int maxi;
         maxi=(20-num);
        while ((fgets(buffer, 250, ptr)) != NULL)
        {
            if (i < 20 && i >= maxi)
                printf("%s", buffer);
            i++;
        }
    }
}

void manage(char** tokens,int num)
{
    if (num==1)
        comhistory(10);
    else if (atoi(tokens[1]) >= 1 && atoi(tokens[1]) <= 10)
        comhistory(atoi(tokens[1]));
}