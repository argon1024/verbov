#include <stdio.h>
#include <string.h>

int main(int argc, char** argv, char** env)
{
	int arg1,arg2;
	if(argc < 2) {
		printf("usage:\t%s param1 param2\n", argv[0]);
		return 0;
	}
	arg1 = atoi(argv[1]);
	arg2 = atoi(argv[2]);
	return 0;
}
