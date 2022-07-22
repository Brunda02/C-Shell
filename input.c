#include "tokenise.c"
#include "processes4.c"
#include "pinfo.c"
#include "commands.c"
#include "repeat.c"
#include "history.c"
#include "headers.h"
#include "fgbg.c"
#include "kill.c"
#include "jobs.c"
#include "pipe4.c"
#include "replay.c"
//#include "signals.c"
//#define Line;
int brunda = -1;

int checkrepi(char *str)
{
   int len = strlen(str);
   int i;
   int x = -1;
   for (i = 0; i < len; i++)
   {
      if (str[i] == '|' || str[i] == '<' || str[i] == '>')
         x = 1;
   }
   return x;
}

void formatinput(char *str)
{
      char str2[500];
      strcpy(str2, str);
      char **list_of_cmds = tokens(str);
      int i = 0;
      while (list_of_cmds[i] != NULL)
      {
         i++;
      }
      int num = i;
      //printf("%d\n",i);
      char **list_of_cmds2 = tokens(str2);
      i = 0;
      while (list_of_cmds2[i] != NULL)
      {
         i++;
      }
      // int num=i;
      //printf("%d\n",num);
      struct easy breaks[num];
      i = 0;
      while (list_of_cmds[i] != NULL)
      {
         breaks[i] = eachcmd(list_of_cmds[i]);
         i++;
      }
      int y;
      for (i = 0; i < num; i++)
      {
         y = checkrepi(list_of_cmds2[i]);
         //printf("%d\n",y);
         if (strcmp(breaks[i].x[0], "cd") == 0 && y == -1)
         {
            // printf("Hello\n");
            funcd(breaks[i]);
         }
         else if (strcmp(breaks[i].x[0], "pwd") == 0 && y == -1)
            funpwd();
         else if (strcmp(breaks[i].x[0], "echo") == 0 && y == -1)
         {
            funecho(breaks[i]);
            //printf("Hello\n");
         }
         else if (strcmp(breaks[i].x[0], "ls") == 0 && y == -1)
            lscmds(breaks[i].x, breaks[i].number);
         else if (strcmp(breaks[i].x[0], "pinfo") == 0 && y == -1)
            handle(breaks[i]);
         else if (strcmp(breaks[i].x[0], "exit") == 0 && y == -1)
            exit(0);
         else if (strcmp(breaks[i].x[0], "repeat") == 0 && y == -1)
            repeat(breaks[i]);
         else if (strcmp(breaks[i].x[0], "history") == 0 && y == -1)
         {
            // printf("Hello\n");
            manage(breaks[i].x, breaks[i].number);
         }
         else if (strcmp(breaks[i].x[0], "jobs") == 0 && y == -1)
            general(breaks[i].x, breaks[i].number);
         else if (strcmp(breaks[i].x[0], "sig") == 0 && y == -1)
            sendsig(breaks[i].x, breaks[i].number);
         else if (strcmp(breaks[i].x[0], "fg") == 0 && y == -1)
            fg(breaks[i].x, breaks[i].number);
         else if (strcmp(breaks[i].x[0], "bg") == 0 && y == -1)
            bg(breaks[i].x, breaks[i].number);
          else if (strcmp(breaks[i].x[0], "replay") == 0 && y == -1)
            replay(breaks[i].x, breaks[i].number);   
         //else check(breaks[i].x,breaks[i].number) ;
         else if (y == 1)
            genbru(list_of_cmds2[i]);
         else
            check(breaks[i].x, breaks[i].number);
      }
      //Line:
   }

