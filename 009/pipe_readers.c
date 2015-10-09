#include <stdio.h>
#include <string.h>


char buf[256];
char buf2[256];

int main(int argc, char** argv, char** env)
{
	FILE *fd;
	char temp_char;
	int len, i;
	
	if(argc < 2) puts("usage:\tpipe_readers -c \'program\'");
	fd = popen(argv[2],"r");
	if(fgets(buf, sizeof(buf), fd) == NULL) puts("Error! len string out of buf");
	len = strlen(buf);
	printf("\nString:%s\nlen=%d\n", buf, len);
#if 0
	for(i=0; i < len; i++){
		temp_char = buf[i];
		buf[i] = buf[len - i -1];
		buf[len-i-1] = temp_char;
	}
	printf("\nReversed string:%s", buf);
#else
	for(i = 0; i < len; i++) {
		buf2[i] = buf[len - i -2];
	}
	buf2[i] = 0;
	printf("\nReversed string:%s", buf2);
#endif
	puts("\n");
	return 0;
}



