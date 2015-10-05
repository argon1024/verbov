#include <stdio.h>
#include <string.h>

char pwd_string[] = {"PWD="};

int main(int argc, char **argv, char **envp)
{
	if(envp == NULL) return 1;
	else             printf("**envp = %p\n", envp);
	while(*envp){
		char *p = strstr(*envp, pwd_string);
		if(*envp == p){
			printf("\ncurrent path: %s\n",p + sizeof(pwd_string));
			break;
		}
		*envp++;
	}
	return 0;
}
