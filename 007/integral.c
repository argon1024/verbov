#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>

// линк по теме
// http://prog-cpp.ru/integral-trapecia/

#define MAX_THREADS	4000

typedef struct params{
	pthread_t	thread_id; 	/* ID returned by pthread_create() */
	int		thread_numb;	/* Application-defined thread # */
	double		wleft;
	double		wright;
} params_t;

double	sum = 0;


void* my_thread_func(void* arg)
{
	params_t* par = (params_t*)arg;
	double delta = (par->wright - par->wleft);
#if 0
	double abs = (par->wright + par->wleft)/2;
	sum = sum + delta * sin(abs);	// y=sine(x)
#else
	double y_left = fabs(sin(delta * par->thread_numb));
	double y_right = fabs(sin(delta * (par->thread_numb + 1)));
	sum += (y_left + y_right) * delta / 2;
#endif
	pthread_exit(0);
}

int main(int argc, char** argv, char** env)
{
	int	i;
	int	ret;
	char	*endprt;
	int	selects;
	double	period;
	double	thread_period;
	params_t	*params;
	if(argc < 3){
		puts("No enough argumrnts.");
		printf("usage: %s N n\n", *(argv + 0));
		return 0;
	}else
	selects = atoi(argv[2]);
	period = strtod(argv[1], &endprt);
	thread_period = period / selects;
	if((argc < 3) || (period <= 0) || (selects <= 0)
	|| (selects > MAX_THREADS) || (endprt == argv[1])){
		puts("Error parsing arguments.");
		printf("usage: %s N n\n", *(argv + 1));
		return 0;
	}else{
		params = calloc(sizeof(params_t), MAX_THREADS);
		for(i = 0; i < selects; i++) {
			params[i].thread_numb = i + 1;
			params[i].wleft = thread_period * i;
			params[i].wright = thread_period * (i + 1);
			if(pthread_create(&params[i].thread_id, NULL, &my_thread_func, &params[i]) != 0) {
				perror("pthread_create");
				return -1;
			}
		}
		for(i = 0; i < selects; i++) {
			ret = pthread_join(params[i].thread_id, NULL);
			if(ret != 0) {
				fprintf(stderr,"ERROR: join() \n");
				return 1;
			}
		}
		printf("Integral y = sin(x) = %f \n",sum);
		free(params);
	}
	return 0;
}
