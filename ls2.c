#include "headers.h"

////problems aligning problem....in ls

char currdir[250];
char homedir[250];
char reldir[250];
char lsrelat[250];

int checkin(char *a)
{
    int z = -1; //file=1,dir=0
    struct stat x,x2;
    char *buff = (char *)malloc(250 * sizeof(char));
    int y = stat(a, &x);
    strcpy(buff, currdir);
    strcat(buff, "/"); //-1 error 0,1 dir,file in relative path 2,3 dir,file if path is absolute
    strcat(buff, a);
    int y2 = stat(buff, &x2);
    if (y2 == 0)
    {
        if (S_ISDIR(x.st_mode) != 0)
            z = 0;
        else
            z = 1;
    }
    else {
    if (y == 0)
    {
        if (S_ISDIR(x.st_mode) != 0)
            z = 2;
        else
            z = 3;
    }
    }
    return z;
}

char *numtomon(int x, char *month)
{
    if (x == 1)
        strcpy(month, "Jan");
    if (x == 2)
        strcpy(month, "Feb");
    if (x == 3)
        strcpy(month, "Mar");
    if (x == 4)
        strcpy(month, "Apr");
    if (x == 5)
        strcpy(month, "May");
    if (x == 6)
        strcpy(month, "Jun");
    if (x == 7)
        strcpy(month, "Jul");
    if (x == 8)
        strcpy(month, "Aug");
    if (x == 9)
        strcpy(month, "Sep");
    if (x == 10)
        strcpy(month, "Oct");
    if (x == 11)
        strcpy(month, "Nov");
    if (x == 12)
        strcpy(month, "Dec");

    return month;
}

//getting for each file or directory
void print(char *dirorfile, char *name) //h =1 if "a" flag comes
{
    char month[4];
    int date;
    int hour;
    int min;
    int mont;
    int year;
    char buff[100];
    struct stat x;
    // if(stat(dirorfile,&x)==0){}
    // else printf("Failed in getting the struct\n");
    int y = stat(dirorfile, &x);
    //////<-------time calculation------->//////////
    time_t mod = x.st_mtime; //modification time
    struct tm t;
    localtime_r(&mod, &t); /* convert to struct tm */
    mont = t.tm_mon + 1;
    date = t.tm_mday;
    hour = t.tm_hour;
    min = t.tm_min;
    year = t.tm_year + 1900;
    numtomon(mont, month);

    //////<-------time calculation------->//////////

    //////<-------size calculation------->//////////
    long long int size = x.st_size;
    //////<-------size calculation------->//////////

    //////<-------permission calculation------->//////////
    char perm[11];
    if (S_ISDIR(x.st_mode) != 0)
        perm[0] = 'd';
    else
        perm[0] = '-';
    if ((x.st_mode & S_IRUSR))
        perm[1] = 'r';
    else
        perm[1] = '-';
    if ((x.st_mode & S_IWUSR))
        perm[2] = 'w';
    else
        perm[2] = '-';
    if ((x.st_mode & S_IXUSR))
        perm[3] = 'x';
    else
        perm[3] = '-';
    if ((x.st_mode & S_IRGRP))
        perm[4] = 'r';
    else
        perm[4] = '-';
    if ((x.st_mode & S_IWGRP))
        perm[5] = 'w';
    else
        perm[5] = '-';
    if ((x.st_mode & S_IXGRP))
        perm[6] = 'x';
    else
        perm[6] = '-';
    if ((x.st_mode & S_IROTH))
        perm[7] = 'r';
    else
        perm[7] = '-';
    if ((x.st_mode & S_IWOTH))
        perm[8] = 'w';
    else
        perm[8] = '-';
    if ((x.st_mode & S_IXOTH))
        perm[9] = 'x';
    else
        perm[9] = '-';
    perm[10] = '\0';
    //////<-------permission calculation------->//////////

    //////<-------number of files calculation------->//////////
    long long int number = x.st_nlink;
    //////<-------number of files calculation------->//////////

    //////<-------owner,group calculation------->//////////
    struct stat info;
    stat(currdir, &info); // Error check omitted
    struct passwd *pw = getpwuid(info.st_uid);
    struct group *gr = getgrgid(info.st_gid);
    char *user = pw->pw_name;
    char *group = gr->gr_name;
    //////<-------owner,groupcalculation------->//////////
    if (year == 2021)
        printf("%s     %lld       %s       %s           %lld %s  %d %d:%d %s\n", perm, number, user, group, size, month, date, hour, min, name);
    if (year < 2021)
        printf("%s     %lld       %s       %s           %lld %s  %d %d %s\n", perm, number, user, group, size, month, date, year, name);
}

//parsing all files and directories

void getall(int m, char* direct)
{
    DIR *dir;
    struct dirent *ent;
    long long int count = 0;
    dir = opendir(direct);
        //printf("%s\n",dir);
    if(dir!=NULL){    
        while ((ent = readdir(dir)))
        {
            count++;
        }
        char allnames[count][100];
        int hidden[count];
        count = 0;
        long long int b = 0, b2 = 0; //blocks
        dir = opendir(direct);
        while ((ent = readdir(dir)))
        {
            struct stat x;
            strcpy(allnames[count], ent->d_name);
            if (allnames[count][0] == '.')
                hidden[count] = 1;
            else
                hidden[count] = 0;
            char *buff = (char *)malloc(sizeof(char) * 250);
            strcpy(buff, direct);
            strcat(buff, "/");
            strcat(buff, allnames[count]);
            if (stat(buff, &x) == 0)
            {
                b = b + x.st_blocks;
                if (hidden[count] == 1)
                    b2 = b2 + x.st_blocks;
            }
            else
            {
                printf("Error in getting stat\n");
            }
            free(buff);
            count++;
        }
        if (m == 3)
            printf("total %llu\n", b / 2);
        if (m == 1)
            printf("total %llu\n", (b - b2) / 2);
        for (int j = 0; j < count; j++)
        {
            char *buff = (char *)calloc(sizeof(char), 250);
            strcpy(buff, direct);
            strcat(buff, "/");
            strcat(buff, allnames[j]);
            if (m == 1 && hidden[j] == 0)
                print(buff, allnames[j]);
            if (m == 2)
                printf("%s\n", allnames[j]);
            if (m == 3)
                print(buff, allnames[j]);
            if (m == 4 && hidden[j] == 0)
                printf("%s\n", allnames[j]);
            free(buff);
        }
    }

}

int lastin(char *str)
{
    int i = 0, x = -1;
    while (str[i] != '\0')
    {
        if (str[i] == '/')
            x = i;
        i++;
    }
    return x;
}

void singledot(int m)
{
    strcpy(lsrelat, currdir);
    getall(m, currdir);
}

void doubledot(int m)
{
    char *name;
    int index;
    index = lastin(currdir);
    name = (char *)malloc(sizeof(char) * 250);
    strncpy(name, &currdir[0], index);
    name[index] = '\0';
    strcpy(lsrelat, name);
    getall(m, name);
    free(name);
}

void tilda(int m)
{
    strcpy(lsrelat, homedir);
    getall(m, homedir);
}


void fileordirectory(int m, int z, char* str)
{
    char *name;
    name = (char *)malloc(sizeof(char) * 250);
    strcpy(lsrelat, currdir);
    if (z == 0)
    {
        strcpy(name, currdir);
        strcat(name, "/");
        strcat(name, str);
        getall(m, name);
 //       printf("%s %s\n",name,str);
    }
     if (z == 1){
         strcpy(name, currdir);
        strcat(name, "/");
        strcat(name, str);
        if(m%2) print(name,str);
        else printf("%s",str);
    }
    if(z == 2){
        // if(m%2) print(str,str);
        // else printf("%s",str);
        getall(m,str);
    }
    if(z==3){
       // getall(m,str);
       if(m%2) print(str,str);
        else printf("%s",str);
    }
    if(z<0) printf("Error\n");
      free(name);  
}

//for handling the flags
void lscmds(char **tokens, int num)
{
    int flag_l = 0, i, j, index, z;
    int flag_a = 0;
    int dcount = -1;
    int array[num];
    int cfilerdir[num];
    int ocount = 0;
    int tcount = 0;
    int prevcount = 0;
    char *name;
    for (i = 0; i < num; i++)
    {
        if (tokens[i][0] == '-')
        {
            for (j = 1; j < strlen(tokens[i]); j++)
            {
                if (tokens[i][j] == 'a')
                    flag_a = 1;
                if (tokens[i][j] == 'l')
                    flag_l = 1;
                if (tokens[i][j] != 'a' && tokens[i][j] != 'l')
                    printf("Incorrect command\n");
            }
        }
        else if (strcmp(tokens[i], ".") == 0)
        {
            ocount++;
        }
        else if (strcmp(tokens[i], "~") == 0)
        {
            tcount++;
        }
        else if (strcmp(tokens[i], "..") == 0)
        {
            prevcount++;
        }
        else
        {
            if (i)
            cfilerdir[dcount + 1] = checkin(tokens[i]);
            array[dcount + 1] = i;
            dcount++;
        }
    }

    //case 1: only l flag //case 2: only a flag //case3: both la flags are set //case4: both are not set
    int m;
    if (flag_l == 1 && flag_a == 0)
        m = 1;
    else if (flag_l == 0 && flag_a == 1)
        m = 2;
    else if (flag_l == 1 && flag_a == 1)
        m = 3;
    else if (flag_l == 0 && flag_a == 0)
        m = 4;

    if ((tcount + ocount + prevcount + dcount) == 1)
    {
        if (tcount == 1) tilda(m);
        if (ocount == 1) singledot(m);
        if (prevcount == 1) doubledot(m);
        if (dcount == 1)  fileordirectory(m,cfilerdir[1],tokens[array[1]]);
    }
    else if ((tcount + ocount + prevcount + dcount) == 0)
    {
        strcpy(lsrelat, currdir);
        getall(m, currdir);
    }
    else
    {
        // printf("Not Supported\n");
        for (int i = 0; i < ocount; i++)
        {
            printf(".:\n");
            singledot(m);
            printf("\n\n");
        }
        for (int i = 0; i < prevcount; i++)
        {
            printf("..:\n");  
            doubledot(m);
            printf("\n\n");
        }
        for (int i = 0; i < tcount; i++)
        {
            printf("%s:\n", homedir);
            tilda(m);
            printf("\n\n"); 
        }
        for (int i = 0; i < tcount; i++)
        {
            printf("%s:\n", homedir);
            tilda(m);
            printf("\n\n"); 
        }
         for (int i = 1; i <= dcount; i++)
        {
            printf("%s:\n", tokens[array[i]]);
            fileordirectory(m,cfilerdir[i],tokens[array[i]]);
            printf("\n\n"); 
        }
    }
}


