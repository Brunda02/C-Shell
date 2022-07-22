#include "headers.h"
//#include "processes4.c"

int jobnum[100];

struct yes{
   char name[50];
   int job;
   pid_t pid;
};

void jobs(int m, int pid, char *str,int job_num) //m for flags
{
   char path_to[100];
   char path_to2[100];
   int a;
   char b[50];
   char c;
   char d[100];
   char state[15];
  // int job_num = 1;
   sprintf(path_to, "/proc/%d/stat", pid);
   FILE *f = fopen(path_to, "r");
   if(f!=NULL){
   fscanf(f, "%d %s %c", &a, b, &c);
   if (c == 'T')
      strcpy(state, "Stopped");
   else
      strcpy(state, "Running");
   //  sprintf(path_to2,"/proc/%d/cmdline",pid);
   //  FILE* f2 = fopen(path_to,"r");
   //  fscanf(f2,"%s",d);
   if (c == 'T' && m == 2)
      printf("[%d] %s %s [%d]\n", job_num, state, str, pid);
   if (c != 'T' && m == 1)
      printf("[%d] %s %s [%d]\n", job_num, state, str, pid);
   if (m == 0)
      printf("[%d] %s %s [%d]\n", job_num, state, str, pid);
   }   
}



void all3(int m)
{
   //char dupli[100][50];
   struct yes dupli[100];
   int cnt=0;
   for(int i=0;i<100;i++){
      if(bru[i].iden!=-1){
      strcpy(dupli[cnt].name,bru[i].name);
      dupli[cnt].job=jobnum[i];
      dupli[cnt].pid=bru[i].pid;
      cnt++;
      }
   }
   //printf("%d\n",cnt);
   //char* temp[50];
   struct yes temp;
   for(int i=0;i<cnt;i++)
      for(int j=i+1;j<cnt;j++){
         if(strcmp(dupli[i].name,dupli[j].name)>0){
            temp = dupli[i];
            dupli[i]=dupli[j];
            dupli[j]=temp;
         }
   }
   for (int i = 0; i < cnt; i++)
   {
     // printf("%s %d %d\n",dupli[i].name,dupli[i].job,dupli[i].pid);
      if (dupli[i].job != -1)
      {
         jobs(m, dupli[i].pid, dupli[i].name,dupli[i].job);
      }
   }
}

void general(char **tokens, int num)
{
   for(int i=0;i<100;i++){
       jobnum[i]=-1;
   }
   int job_num = 1;
   for (int i = 0; i < 100; i++)
   {
      if (bru[i].iden != -1)
      {
         jobnum[i]=job_num;
         job_num++;
      }
   }
   //printf("%d\n",job_num);
   if (num == 1)
   {
      all3(0);
   }
   if (num == 2)
   {
      if (strcmp(tokens[1], "-r") == 0)
         all3(1);
      else if (strcmp(tokens[1], "-s") == 0)
         all3(2);
      else
         printf("Wrong Flag\n");
   }
}