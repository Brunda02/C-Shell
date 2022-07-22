#ifndef __HEADERS_H
#define __HEADERS_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<unistd.h>
#include<fcntl.h>
#include <limits.h>
#include<sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <time.h>

struct easy{
    char** x;
    int number;
};

struct bg{
    int iden;
    pid_t pid;
    char* name;
};

struct bg bru[100];
int totalbackground=0;

struct fg{
    pid_t pid;
    char* name;
};

struct fg fore;

pid_t bid;
int out;
int out2;
int zeb=0;

#endif 