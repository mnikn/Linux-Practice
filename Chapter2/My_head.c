#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define OFFSET_SIZE 400
#define READ_SIZE sizeof(char)

int main(int argc,char *argv[])
{
    if(argc != 2){
        fputs("Error : you need two args.",stderr);
        exit(1);
    }

    int fd = open(argv[1],O_RDONLY);
    if(fd == -1){
        perror(argv[1]);
        exit(1);
    }

    char buf[OFFSET_SIZE];

    read(fd,buf,OFFSET_SIZE);
    for(int i=0;i<OFFSET_SIZE;++i){
        if(i>=100 && buf[i] == '\n'){
            printf("%c",buf[i]);
            break;
        }
        printf("%c",buf[i]);
    }

    close(fd);
    return 0;
}
