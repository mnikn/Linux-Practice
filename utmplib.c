#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define NRECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utm_buf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

int utmp_open(char *file_name)
{
	fd_utmp = open(file_name,O_RDONLY);
	cur_rec = num_recs = 0;
	return fd_utmp;
}

int utmp_reload()
{
	int amt_read;
	amt_read = read(fd_utmp,utm_buf,NRECS * UTSIZE);
	num_recs = amt_read/UTSIZE;
	cur_rec = 0;
	return num_recs;
}

struct utmp* utmp_next()
{
	struct utmp *recp;
	if(fd_utmp == -1)  return NULLUT;
	if(cur_rec == num_recs && utmp_reload() == 0)  return NULLUT;
	recp = (struct utmp*) &utm_buf[cur_rec * UTSIZE];
	++cur_rec;
	return recp;
}

int utmp_close()
{
	if(fd_utmp != -1)
		fd_utmp = close(fd_utmp);
	return fd_utmp;
}