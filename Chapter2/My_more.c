#include <stdio.h>
#include <stdlib.h>
#define PAGE_LEN 24
#define LINE_LEN 512

/*
*   more command,read file and show text.
* Enter space mean advance 512 chars,enter
* Enter mean advance 1 line.
*/

int see_more(FILE *);
void do_more(FILE *);

int main(int argc,char *argv[])
{
    if(argc == 1){
        do_more(stdin);
    }

    while(--argc){
        FILE *file = fopen(* ++argv,"r");
        if(file == NULL){
            fprintf(stderr,"File %s cannot open.\n",*argv);
            exit(1);
        }
        do_more(file);
        fclose(file);
    }
    return 0;
}

/*
* read command from stdin
*/
int see_more(FILE *fp_tty)
{
    int command;
    while((command = getc(fp_tty)) != EOF){
        if(command == '\n')      return 1;
        else if(command == ' ')  return PAGE_LEN;
        else if(command == 'q')  return 0;
        else                    fprintf(stderr,"Command %c is not define.",command);
    }
}

/*
* show the text in the file
*/
void do_more(FILE *file)
{
    char context[LINE_LEN];
    int reply;
    int num_of_lines = 0;
    FILE *fp_tty = fopen("/dev/tty","r");
    while(fgets(context,LINE_LEN,file)){
        if(num_of_lines == PAGE_LEN){
            reply = see_more(fp_tty);
            if(reply == 0)  break; //when enter 'q',quit
            num_of_lines -= reply;
        }
        if(fputs(context,stdout) == EOF) exit(1);
        ++num_of_lines;
    }
}
