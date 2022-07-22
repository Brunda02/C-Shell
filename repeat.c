#include "headers.h"

void clear()
{
}

void repeat(struct easy b)
{
    
    char** str;
    int y=b.number-2;
    str=(char**)malloc((sizeof(char*))*y);
    int num=atoi(b.x[1]);
    //printf("%d\n",num);
    for(int i=2;i<b.number;i++){
      str[i-2]=strdup(b.x[i]);
    }
    str[b.number-2]='\0';
  //  printf("%s %s\n",str[0],str[1]);
    struct easy a;
    a.x=str;
   // printf("%s %s %s",a.x[0],a.x[1],a.x[2]);
    a.number=((b.number)-2);
    if (strcmp(a.x[0], "cd") == 0)
    {
        for(int i=0;i<num;i++)
        funcd(a);
    }
    else if (strcmp(a.x[0], "pwd") == 0)
    {
        for(int i=0;i<num;i++)
        funpwd();
    }
    else if (strcmp(a.x[0], "echo") == 0)
    {
        for(int i=0;i<num;i++)
        funecho(a);
    }
    else if (strcmp(a.x[0], "ls") == 0)
    {
        for(int i=0;i<num;i++)
        lscmds(a.x, a.number);
    }
    else if (strcmp(a.x[0], "pinfo") == 0)
    {
        for(int i=0;i<num;i++)
        handle(a);
    }
    else if (strcmp(a.x[0], "exit") == 0)
    {
        for(int i=0;i<num;i++)
        exit(0);
    }
    else if (strcmp(a.x[0], "repeat") == 0)
    {
        for(int i=0;i<num;i++)
        repeat(a);
    }
    //else if(strcmp(breaks[i].x[0],"history")==0)  manage(breaks[i].x);
    else
    {
       // printf("%s %s %s\n",str[0],str[1],str[2]);
        for(int i=0;i<num;i++)
        check(a.x, a.number);
    }
}
