#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

char buf[256], buf1[256];
int return_val;

void my_signal_handler(int sig)
{
	switch(sig) {
		case SIGINT:
			puts("Goodbye");
			exit(0);
		default:
			break;
	}
}


int main(int argc, char** argv, char** env)
{
	puts("My Shell v1.0 (c) Vasya Pupkin");
	if(argc > 1 ) {
		puts("usage: shell\t<no arguments>\n");
		puts("press ctrl+c to exit\n");
		fflush (stdout);
		exit(0);
	}
	signal(SIGINT, my_signal_handler);
	sprintf(buf, "%s:%s", getenv("PATH"), getcwd(buf1, sizeof(buf1)));
	setenv("PATH", buf, 1);
	while(1) {
		printf("--> ");
		fflush (stdout);
		fgets(buf, sizeof(buf), stdin);
		return_val = system(buf);
	}
}
