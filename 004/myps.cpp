
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


#define BUF_LEN 80

using namespace std;

int my_getppid( int pid )
{
	int ret=-1;
	char file_name[BUF_LEN];

	sprintf(file_name, "/proc/%d/status", pid);

	FILE* fd = fopen(file_name, "r");
	if (fd == NULL) {
		perror("open file");
		return -1;
	}

	char buff[BUF_LEN];

	while( fgets( buff, BUF_LEN, fd ) != NULL ) {
        	if ( strstr ( buff, "PPid:") == NULL)	continue;
		else {
			ret = atoi (buff+5);
			break;
		}
    	}
	fclose(fd);
	return ret;
}


int main(int argc, char** argv, char** env)
{
	int ppid = 1;
	int pid = 1;
	if (argc <2) {
		DIR* p_dir;
		printf("\nNo input process, print all possible.\n ");
		p_dir = opendir("/proc");
		struct dirent* dp = readdir(p_dir);
		while(dp) {
			pid = strtol(dp->d_name, NULL, 10);
			if (pid <= 0) { 
				printf("Error. PID = %d", pid);
			} else {
				printf("%d", pid);
				while((ppid = my_getppid(pid)) > 0) {
					printf(" -> %d", ppid);
					pid=ppid;
				}
			}
			dp = readdir(p_dir);
			cout << endl;
		}
		closedir(p_dir);
	} else {
		pid = atoi (argv[1]);
		printf("%d ", pid);
		while( (ppid=my_getppid(pid))>0)
		{
			printf(" -> %d", ppid);
			pid=ppid;
		}
	}
	cout << endl;
	return 0;
}
