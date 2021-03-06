/* This file generated by mkprj.sh */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

#define	MAX_BUF	256

int main(int argc, char** argv, char** env)
{
	//int ;
	DIR *proc_dir, *proc_dir1;
	int pid, tpid, multi = 0;
	char *buf;
	struct dirent *dp, *dp1;
	if(argc < 2) {
		printf("usage:\t%s [process]\n", argv[0]);
		puts("If process = \"all\", then print all processes.");
		return 0;
	}
	if(strcmp(argv[1], "all\0") == 0){
		puts("Print all processes.");
		multi = 1;
		proc_dir1 = opendir("/proc\0");
		if(proc_dir1 == NULL) {
			puts("Error opendir \"/proc\"!");
			exit(-1);
		}
	} 
	do {
		if(multi == 1){
			dp1 = readdir(proc_dir1);
//			printf("proc_dir1=%s\n", dp1->d_name);
			if(dp1 == NULL) {
				closedir(proc_dir1);
//				puts("dp1 == NULL");
				break;
			}
			pid = strtol(dp1->d_name, NULL, 10);
			if(errno == ERANGE) {
				continue;
//				puts("pid = 0, exiting.");
				break;
			}
		} else {
			pid = atoi(argv[1]);
		}
		buf = calloc(sizeof(buf), MAX_BUF);
		if(buf == NULL) {
			puts("Error memory allocate.");
			exit(-1);
		}
		sprintf(buf, "/proc/%d/task", pid);
		proc_dir = opendir(buf);
		free(buf);
		if(proc_dir == NULL) {
			if(multi)	continue;
			else {
				printf("Error process %d \n", pid);
				exit(-1);
			}
		}
		dp = readdir(proc_dir);
		while(dp) {
			tpid = strtol(dp->d_name, NULL, 10);
			if(tpid > 0) {
				if (tpid==pid)	//	(errno != ERANGE)
					printf("%d - root task\n", pid);
				else
					printf( "\t|-%d\n", tpid);
			}
			dp = readdir(proc_dir);
		}
		closedir(proc_dir);
	}while(multi);
	exit(0);

}
