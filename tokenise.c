#include"headers.h"

struct easy eachcmd(char* cmd){
    
    struct easy a;
    char** arguments;
    int k = 0;
    char* tokenized;
    arguments = calloc(1, sizeof (char *));
    tokenized = strtok(cmd, "\t ");
    while (tokenized != NULL) {
        arguments[k] = tokenized;
        ++k;
        arguments = realloc(arguments, sizeof (char *) * (k + 1));            
        tokenized = strtok(NULL, "\t ");
    }
    arguments[k] = NULL;
    a.x=arguments;
    a.number=k;
    return a;
}


char** tokens(char* str)
{
    char** cmds;
    int k = 0;
    char* token;
    cmds = calloc(1, sizeof (char *));
    token= strtok(str, ";");
    while (token != NULL) {
        cmds[k] = token;
        ++k;
        cmds = realloc(cmds, sizeof (char *) * (k + 1));             
        token = strtok(NULL, ";");
    }
    cmds[k] = NULL;
    return cmds;
}

// int main()
// {
//    char str[80];
//    printf("Hello");
//    gets(str);
//    char** cmds=tokens(str);
//    int i=0;
//    struct easy a[15];
//    while(cmds[i]!=NULL){
//       a[i]= eachcmd(cmds[i]);
//       printf("%d\n",a[i].number);
//       for(int j=0;j<a[i].number;j++){
//           printf("%s\n",a[i].x[j]);
//       }
//       i++;
//    }
// }




