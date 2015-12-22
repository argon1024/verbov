#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv, char** env)
{
	int cmd;
	while(1) {
		puts("Type one number:\n\"cmd1\"\t-\tview pkt mode\n"
					"\"cmd2\"\t-\tuserspace - > net\n"
					"\"cmd3\"\t-\tnet -> userspace\n");
		fscanf(stdin, "cmd%d", &cmd);
		printf("Selected %d\n", cmd);
	}
	return 0;
}

