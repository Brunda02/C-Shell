#include "headers.h"

struct Node
{
    char* names;
    pid_t pid;
    struct Node *next;
};

struct Node* head = NULL;
struct Node* x;
char process[20];

void push(struct Node **head_ref, int new_data, char *name)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->pid = new_data;
    new_node->names=(char*)malloc(20*sizeof(char));
    //new_node->names=name;
    strcpy(new_node->names, name);
    //printf("%s\n", new_node->name);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void delete (struct Node **head_ref, pid_t key)
{
    //char* x = NULL;
    struct Node *temp = *head_ref, *prev;
    x=NULL;

    if (temp != NULL && temp->pid == key)
    {
        *head_ref = temp->next; // Changed head // free old head
         x = temp;
         strcpy(process,x->names);
        free(temp);
        return;
    }

    while (temp != NULL && temp->pid != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return;
    }

        x = temp;
        strcpy(process,x->names);
        prev->next = temp->next;
        free(temp);
}

void search(int pid)
{
    int i;
    for(i=0;i<100;i++)
    {
       if(bru[i].pid==pid)
       {
           bru[i].iden==-1;
       } 
    }
}

void hel()
{
    int status;
    pid_t cpid;
    cpid = waitpid(-1, &status, WNOHANG);
    delete (&head, cpid);
    if (x == NULL)
    {
    }
    else if (x->pid = cpid)
    {
        //printf("%s",x->name);
        search(cpid);
        printf("%s with pid %d exited normally or abnormally\n", process, cpid);
    }
}
