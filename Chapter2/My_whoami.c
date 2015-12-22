#include "utmplib.c"
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    struct utmp *cur_utmp;
    int utmp_fd = utmp_open(UTMP_FILE);
    while((cur_utmp = utmp_next()) != (struct utmp*)NULL){
        if(cur_utmp->ut_type == USER_PROCESS){
            printf("%s",cur_utmp->ut_name);
            break;
        }
    }
    return 0;
}
