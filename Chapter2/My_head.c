#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define OFFSET_SIZE 100
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
    fputs(buf,stdout);

    close(fd);
    return 0;
}
