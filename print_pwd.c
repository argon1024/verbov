#include <stdio.h>
#include <string.h>

char string_pwd[] = {"PWD="};

int main(int argc, char *argv[], char **envp)
{
	if(envp == NULL)
		return 1;
	else
		printf("%p\n", envp);

	while(*envp){
		char *p = strstr(*envp, string_pwd);
		if(*p == 0){
			printf("%s\n", *p+sizeof(string_pwd));
		}
		return 0;
		*envp++;
	}
        return -1;
}

