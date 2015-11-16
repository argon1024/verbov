#define _GNU_SOURCE
#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

int main(int argc, char** argv, char** env)
{
	pid_t pid_child;
	struct utsname uts;
	
	if(argc < 2) {
		puts("usage:\tuts_namespace_changer <child-hostname>");
		return 1;
	}

	switch(pid_child = fork()) {
	case -1:
		perror("fork error");
		exit(1);
	case 0:
		if (unshare(CLONE_NEWUTS) == -1)
			errExit("unshare");
		if (uname(&uts) == -1)
			errExit("uname");
		if (sethostname(arg, strlen(arg)) == -1)
			errExit("sethostname");
		sprintf(cmd,"ls -l /proc/%d/ns",getpid());
		cat(cmd,"parent namespaces");

		sprintf(cmd,"ls -l /proc/%d/ns",pid_child);
		cat(cmd,"child namespaces");
				break;
	
	default:
		printf("PID of child created by fork() is %ld\n", (long) pid_child);
		printf("uts.nodename in parent: %s\n", uts.nodename);

		break;
	}
	return 0;
}
