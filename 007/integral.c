#include <pthread.h>
#include <stdio.h>

struct params {
	int	numb;
	double	wleft;
	double	wright;
};


int main(int argc, char** argv, char** env)
{
	if(argc < 3 )	printf("usage: integfral N n\n");
	else{
		int N = atoi(argv[1]);
		int n = atoi(argv[2]);
		for(;;) {
		
		}
	}
	return 0;
}
