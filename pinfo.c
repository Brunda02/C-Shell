#include "headers.h"

int  get(pid_t pid)
{
    int z=0;
    for(int i=0;i<totalbackground;i++){
      if((bru[i].pid) == pid) z=1;
    }
    return z;
}

//for every process
void pinfo(pid_t pid)
{
    char path_to[100];
    char a;int z;char str[3];
    unsigned long long int b;int bi;
    char c[50];
     printf("pid-- %d\n",pid);
     z=get(pid);
    //  strcpy(path_to,"/proc/");
    // strcat(path_to,"pid");
    // strcat(path_to,"/status")
    sprintf(path_to,"/proc/%d/stat",pid);
    //strcat(path_to,"/status");
    // int fp= open(path_to,O_RDONLY,0600); 
    FILE* f = fopen(path_to,"r");
    // long long int sz;
    // sz=lseek(fp,0,SEEK_END);
    // char buf[sz+1];
    if(!f) printf("Not able to open the file\n");
    else{
    //   read(fp,buf,sz);
    //   // sscanf(buf,"Name:\t%s",c);
    //   fscanf(f,"State:\t%c",&a);
    //   fscanf(f,"Pid:\t%d",&bi);
    //   printf("Process Status -- %c\n",a);
    //   fscanf(f,"VmSize:\t%lu",&b);
    //   printf("Memory-- %lu\n",b);
    // //  printf("Memory-- %d\n",bi);
    int i1,i2,i3,i4,i5;long int l1,l2,l3,l4,l5,l6; unsigned long int lu1,lu2,lu3,lu4,lu5,lu6,lu7;unsigned int u1;
    fscanf(f,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu",&bi,c,&a,&i1,&i2,&i3,&i4,&i5,&u1,&lu1,&lu2,&lu3,&lu4,&lu5,&lu6,&l1,&l2,&l3,&l4,&l5,&l6,&b,&lu7);
      fclose(f);
      //printf("Process Status -- %c\n",a);
      str[0]=a;
      str[1]='\0';
     // printf("%s %d\n",str,z);
      if(z==0) strcat(str,"+");
      printf("Process Status -- %s\n",str);
      printf("Memory -- %lu {Virtual Memory}\n",lu7);
      //printf("%d %s %c %lu\n",bi,c,a,lu7);
    }
     sprintf(path_to,"/proc/%d/exe",pid);
    int fp2= open(path_to,O_RDONLY,0600);
    long long int sz2;
    sz2=lseek(fp2,0,SEEK_END);
    char buf2[sz2+1];
    //strcat(path_to,"/exe");
    // if(fp2<0) printf("Error while opening the file\n");
    // else{
      int x=-1;
      x=readlink(path_to,buf2,sz2);
      if(x<0) printf("Error--->!\n");
      else{
        printf("Executable path-- %s\n",buf2);
      }
    // }
    
}

//for all process

void all()
{
    pid_t pid;
    pid=getpid();
    pinfo(pid);
}

void handle(struct easy a)
{
  if(a.number==1) all();
  else if(a.number==2) {
    int val=atoi(a.x[1]);
    //printf("%d\n",val);
    pinfo(val);
  }
  else{
    printf("Error\n");
  }
}