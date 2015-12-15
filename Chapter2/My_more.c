#include <stdio.h>
#include <stdlib.h>
#define PAGE_LEN 24
#define LINE_LEN 512

int see_more(FILE *cmd)
{
	char c;
	printf("\033[7m more? \033[m");
	while( (c = getc(cmd)) != EOF){
		if(c == 'q')  return 0;			//quit
		if(c == ' ')  return PAGE_LEN;  //next page
		if(c == '\n') return 1;			//next line
	}
	return 0;
}

void do_more(FILE *fp)
{
	char line[LINE_LEN];
	int line_num = 0;
	int reply;
	FILE *fp_tty = fopen("/dev/tty","r");
	if(fp_tty == NULL)  exit(1);
	while(fgets(line,LINE_LEN,fp)){
		if(line_num == PAGE_LEN){
			reply = see_more(fp_tty);
			if(reply == 0)  break;
			line_num -= reply;
		}
		if(fputs(line,stdout) == EOF) exit(1);
		++line_num;
	}
} 

int main(int argc,char **argv)
{
	FILE *fp;
	if(argc == 1)  do_more(stdin);
	else{
		while(--argc){
			if((fp = fopen(* ++argv,"r")) != NULL){
				do_more(fp);
				fclose(fp);
			}
			else  exit(1);
		}
	}
	return 0;
}
