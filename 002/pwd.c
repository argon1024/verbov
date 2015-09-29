#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	if(envp == NULL) return -1;
	while(*envp++){
		char *p = strstr(*envp, "PWD=");
		if(*envp == p){
			printf("\ncurrent path: %s\n",p+4);
			break;
		}
	}
	return 0;
}
