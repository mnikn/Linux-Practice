#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include "utmplib.c"
#include <time.h>

#define SHOW_HOST

void show_time(long time_interval)
{
	char *cp = ctime(&time_interval);
	printf("%12.12s",cp+4);
}


void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)  return;
	printf("%-8.8s",utbufp->ut_name);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
	show_time(utbufp->ut_time);
	#ifdef SHOW_HOST
		printf("(%s)",utbufp->ut_host);
	#endif
	printf("\n");
}

int main(int argc,char **argv)
{
	struct utmp *cur_utmp;
	
	
	if(utmp_open(UTMP_FILE) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while((cur_utmp = utmp_next()) != (struct utmp*)NULL){
		show_info(cur_utmp);
	}
	utmp_close();
	return 0;
}
