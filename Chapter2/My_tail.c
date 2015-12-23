#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 4096

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

    char buf[BUFF_SIZE];
    while(read(fd,buf,BUFF_SIZE));
    close(fd);

    int start_n = 0,count = 0;
    for(int i = 0;i<strlen(buf) && count != 10;++i){
        if(buf[i] == '\n' && count != 10){
            start_n = i;
            ++count;
        }
    }

    for(int i = start_n;i<strlen(buf);++i){
        printf("%c",buf[i]);
    }


    return 0;
}
