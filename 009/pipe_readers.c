#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[256];
char buf2[256];

int main(int argc, char** argv, char** env)
{
	FILE *fd;
	int i, len;
	
	if(argc < 2) puts("usage:\tpipe_readers -c \'program\'");
	fd = popen(argv[2],"r");
	if(fd == NULL) {
		fprintf(stderr, "Error opening pipe %s.\n", argv[1]);
		exit(-1);
	}
	while(fgets(buf, sizeof(buf) - 1, fd) != NULL) {
		len = strlen(buf);
		for(i = 0; i < len; i++) {
			buf2[i] = buf[len - i -2];
		}
		buf2[i] = 0;
		printf("%s", buf2);
	}
	puts("\n");
	return 0;
}



