#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 4096
#define READ_SIZE sizeof(char)

/*
*   show 10 lines in the first head.
* count '\n',if number of '\n' equals 10,return
*/

void show_head(int);

int main(int argc,char *argv[])
{
    if(argc == 1){
        exit(1);
    }

    int cur_rec = 0;
    while(--argc){
        int fd = open(* ++argv,O_RDONLY);
        show_head(fd);
        close(fd);
    }
    return 0;
}

void show_head(int fd)
{
    char buff[BUFF_SIZE];
    int begin_index = 0,cur_index = 0;
    int line_count = 0;
    while((cur_index += read(fd,buff,BUFF_SIZE)) && line_count != 10){
        for(int i = begin_index;i < cur_index && line_count != 10;++i){
            if(buff[i] == '\n') ++line_count;
            printf("%c",buff[i]);
        }
        begin_index = cur_index;
    }
}
