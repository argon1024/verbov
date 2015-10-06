#include <stdio.h>
#include <string.h>


char buf[256];

int main(int argc, char** argv, char** env)
{
	FILE *fd;
	char temp_char;
	int len, i;
	
	if(argc < 2) puts("usage:\tpipe_readers -c \'program\'");
	fd = popen(argv[2],"r");
	if(fgets(buf, sizeof(buf), fd) == NULL) puts("Error! len string out of buf");
	len = strlen(buf);
	printf("\nString:%s\nlen=%d", buf, len);
	for(i=0; i < len; i++){
		temp_char = buf[i];
		buf[i] = buf[len - i -1];
		buf[len-i-1] = temp_char;
	}
	printf("\nReversed string:%s", buf);
	puts("\n");
	return 0;
}



