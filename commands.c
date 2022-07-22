#include "headers.h"
#include "ls2.c"

char *mainline;
int ischanged = 0; //This is for OLPWD bit.
char prevcd[2][250];
int l=0;

void swap(){
   char* temp=(char*)malloc(250*sizeof(char));
   strcpy(temp,prevcd[0]);
  strcpy(prevcd[0],prevcd[1]);
  strcpy(prevcd[1],temp);
}

void change(){
   if(l==0){
      strcpy(prevcd[0],homedir);
      strcpy(prevcd[1],homedir);
      l++;
   }
   strcpy(prevcd[0],prevcd[1]);
   strcpy(prevcd[1],currdir);
}

char *relativepath()
{
   int i, j;
   int len = strlen(homedir);
   int len2 = strlen(currdir);
   if (len2 > len)
   {
      for (i = 0; i < len; i++)
      {
         if (currdir[i] == homedir[i])
         {
         }
         else
            break;
      }
      reldir[0] = '~';
      int k = 1;
      for (j = i; j < len2; j++)
      {
         reldir[k] = currdir[j];
         k++;
      }
      reldir[k] = '\0';
      // strncpy(reldir,currdir+i,len2-i);
      strcat(reldir, "$ ");
   }
   if (len2 == len)
   {
      strcpy(reldir, "~$ ");
   }
   if (len2 < len)
   {
      strcpy(reldir, currdir);
      strcat(reldir, "$ ");
   }
}

char *pathofcurrdir()
{
   // char* currdir=(char*)malloc(250*sizeof(char));
   if (getcwd(currdir, 250))
   {
   }
   else
      printf("Absolute address is not obtained\n");
   return currdir;
}

void funecho(struct easy a)
{
   for (int i = 1; i < a.number; i++)
   {
      printf("%s ", a.x[i]);
   }
   printf("\n");
}

void funcd(struct easy a)
{
   if (a.number == 2)
   {
      char buff[250];
      if (strcmp(a.x[1], "~") == 0)
      {
         strcpy(currdir, homedir);
         relativepath();
         change();
         ischanged = 1;
      }
      else if (strcmp(a.x[1], "-") == 0)
      {
         if (ischanged == 0)
            printf("OLPWD bit is not set\n");
         else
         {
            swap();
            printf("%s\n", prevcd[1]);
            strcpy(currdir,prevcd[1]);
            relativepath();
         }
      }
      else
      {
         strcpy(buff, currdir);
         strcat(buff, "/");
         strcat(buff, a.x[1]);
         if (chdir(buff) == 0)
         { 
            pathofcurrdir();
            relativepath();
             change(); 
            ischanged = 1;
         }
         else if (chdir(a.x[1]) == 0)
         { 
            pathofcurrdir();
            relativepath();
             change(); 
            ischanged = 1;
         }
         else{
            perror("Error ");
         }
      }
   }
   else if (a.number == 1)
   {
      strcpy(currdir, homedir);
      change();
      ischanged = 1;
   }
   else
   {
      printf("bash: cd: too many arguments\n");
   }

}

void funpwd()
{
   printf("%s\n", pathofcurrdir());
}
