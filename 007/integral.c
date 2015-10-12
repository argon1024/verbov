#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>


#define MAX_THREADS	32

typedef struct params{
	double	numb;
	double	wleft;
	double	wright;
} params_t;

double	sum;


params_t* param_list[MAX_THREADS];

void* my_thread_func(void* arg)
{
	params_t* par = (params_t*)arg;
	double delta = (par->wright - par->wleft);
	double abs = (par->wright + par->wleft)/2;

//	par->result= delta*abs;	// y=x
	sum = delta * sin(abs);	// y=sine(x)
	//printf("%e  %e  %e\n",par->left, par->right, par->result);
    return 0;
}

int main(int argc, char** argv, char** env)
{
	int	i, ret;
	char	*endprt;
	int	selects;
	double	period;
	double	thread_period;
	pthread_t thread[MAX_THREADS];
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
		puts("Error parsing arguments.\n");
		printf("usage: %s N n\n", *(argv + 1));
		return 0;
	}else{
		for(i = 0; i < selects; i++) {
			param_list[i]->wleft = thread_period * i;
			param_list[i]->wright = thread_period * (i + 1);
			if(pthread_create(&thread[i], NULL, &my_thread_func, &param_list[i]) != 0) {
				perror("pthread_create");
				return -1;
			}
		}
		sum = 0;
		for(i = 0; i < selects; i++) {
			if(pthread_join(thread[i], NULL) != 0) {
				fprintf(stderr,"ERROR: join() \n");
				return 1;
			}
		}		
		printf("Integral y = sin(x) = %f \n",sum);
	}
	return 0;
}
