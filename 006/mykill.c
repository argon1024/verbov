#include <signal.h>
#include <stdio.h>

int main(int argc, char** argv, char** env)
{
	if(argc < 3 )	printf("usage: mykill [pid] [signal]\n");
	else{
		int PID = atoi(argv[1]);
		int SIG = atoi(argv[2]);
		kill(PID, SIG);
		printf("Sended signal=%d to process %d\n", SIG, PID);
	}
	return 0;
}
