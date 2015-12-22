#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

void show_info(struct utmp *);

int main(int argc,char *argv[])
{
    int fd = open(UTMP_FILE,O_RDONLY);
    struct utmp cur_record;
    int rec_len = sizeof(cur_record);
    while(read(fd,&cur_record,rec_len) == rec_len){
        show_info(&cur_record);
    }
    return 0;
}

void show_info(struct utmp *utmp_fp)
{
    printf("%-8.8s ",utmp_fp->ut_name);
    printf("%-8.8s ",utmp_fp->ut_line);
    printf("%10ld",utmp_fp->ut_time);
    printf("(%s)\n",utmp_fp->ut_host);
}



