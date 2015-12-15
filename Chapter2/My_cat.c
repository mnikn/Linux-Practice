#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define READ_SIZE sizeof(char)
#define BUFF_SIZE 4096

int main(int argc,char *argv[])
{
    //check args num
    if(argc != 2){
        fprintf(stderr,"Error : You need two args.");
        exit(1);
    }

    int fd = open(argv[1],O_RDONLY);

    //check if file error
    if(fd == -1){
        perror(argv[1]);
        exit(1);
    }

    char buf[BUFF_SIZE];
    while(read(fd,buf,READ_SIZE)){
        if(fputs(buf,stdout) == EOF) exit(1);
    }
    close(fd);
    return 0;
}
