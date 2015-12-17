#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void do_ls(char dir_name[])
{
    DIR *dir_ptr;
    struct dirent *direntp;
    if((dir_ptr = opendir(dir_name)) == NULL){
        fprintf(stderr,"Open dir error!\n");
        exit(1);
    }
    while((direntp = readdir(dir_ptr)) != NULL){
        printf("%s\n",direntp->d_name);
    }
    closedir(dir_ptr);
}

int main(int argc,char *argv[])
{
    if(argc == 1)  do_ls(".");
    else{
        while(--argc){
            printf("%s:\n",* ++argv);
            do_ls(*argv);
        }
    }
    return 0;
}
