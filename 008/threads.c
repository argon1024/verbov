#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>
#include <signal.h>

#define MAX_THREADS	4000

typedef struct params{
	pthread_t	thread_id; 	/* ID returned by pthread_create() */
	int		thread_numb;	/* Application-defined thread # */
	double		wleft;
	double		wright;
} params_t;

params_t	*params;
int		threads;


void* my_thread_func(void* arg)
{
	int s;
//	s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	while(1)
		sleep(1000);
//	pthread_exit(0);
}

void my_signal_handler(int sig)
{
	int i, ret;
	switch(sig) {
		case SIGINT:

			for(i = 0; i < threads; i++) {
				pthread_cancel(params[i].thread_id);
				ret = pthread_join(params[i].thread_id, NULL);
				if(ret != 0) {
					fprintf(stderr,"ERROR: join() \n");
					break;
				}
			}
			puts("Goodbye");
			free(params);
			exit(0);
		default:
			break;
	}
}

int main(int argc, char** argv, char** env)
{
	int	i;
	int	ret;
	if(argc < 2){
		puts("threads - create [num] thread and kill them by ctrl+c");
		puts("usage:\t./threads [num threads]");
		exit(0);
	}
	threads = atoi(argv[1]);
	signal(SIGINT, my_signal_handler);	
	params = calloc(sizeof(params_t), threads);
	for(i = 0; i < threads; i++) {
		params[i].thread_numb = i + 1;
		if(pthread_create(&params[i].thread_id, NULL, &my_thread_func, &params[i]) != 0) {
			perror("pthread_create");
			return -1;
		}
	}
	printf("Started %d thread(s)!\nOwn PID=%d\n", threads, getpid());
	while(1)	sleep(10);
	free(params);
	return 0;
}

