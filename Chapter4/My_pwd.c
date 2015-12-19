#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFF_SIZE 4096

ino_t get_inode(char*);
void print_path_to(ino_t);
void inum_to_name(ino_t,char*,int);

int main()
{
    print_path_to(get_inode("."));
    putchar('\n');
    return 0;
}

void print_path_to(ino_t this_inode)
{
    struct dirent *chdir();
    ino_t my_inode;
    char its_name[BUFF_SIZE];
    if(get_inode("..") != this_inode){
        chdir("..");
        inum_to_name(this_inode,its_name,BUFF_SIZE);
        my_inode = get_inode(".");
        print_path_to(my_inode);
        printf("/%s",its_name);
    }
}

void inum_to_name(ino_t inode_to_find,char *name_buf,int buf_len)
{
    DIR *dir_ptr;
    struct dirent *dirent_tp;
    if((dir_ptr = opendir(".")) == NULL){
        perror(".");
        exit(1);
    }

    while((dirent_tp = readdir(dir_ptr)) != NULL){
        if(dirent_tp->d_ino == inode_to_find){
            strcpy(name_buf,dirent_tp->d_name);
            name_buf[buf_len - 1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }
    fprintf(stderr,"Error happens when find inode %d",inode_to_find);
    exit(1);
}

ino_t get_inode(char *file_name)
{
    struct stat info;
    if(stat(file_name,&info) == -1){
        perror(file_name);
        exit(1);
    }
    return info.st_ino;
}
