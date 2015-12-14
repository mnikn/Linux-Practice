#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
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
	struct utmp current_record;
	int utmp_fd;
	int reclen = sizeof(current_record);
	
	if((utmp_fd = open(UTMP_FILE,O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmp_fd,&current_record,reclen) == reclen){
		show_info(&current_record);
	}
	close(utmp_fd);
	return 0;
}
