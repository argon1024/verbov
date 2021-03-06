/* This file generated by mkprj.sh */
#include <stdio.h>
#include <string.h>

#define BUFLEN	100

int main(int argc, char** argv, char** env)
{
	char buf[BUFLEN], *idx;
	int cnt = 0;
	FILE *fd;
	if(argc != 3) {
		printf("USAGE:\t%s <string> <filename>\n", argv[0]);
		return -1;
	}
	while(fgets(buf, BUFLEN, stdin) != NULL) {
		idx = buf;
		while((idx = strstr(idx, argv[1])) != NULL) cnt++,idx++;
		fputs(buf, stdout);
	}
	fclose(stdout);
	
	if((fd = fopen(argv[2], "w")) == NULL) {
		perror(argv[2]);
		return -1;
	}
	fprintf(fd, "%d", cnt);
	fclose(fd);

	return 0;
}
