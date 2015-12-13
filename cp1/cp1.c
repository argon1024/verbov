#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>


sigset_t	set; 
static struct sigaction act_s;

void usr_sig_handler(int sig)
{
        printf("sig = %d", sig);
        switch(sig) {
                case SIGINT:
			syslog(LOG_NOTICE, "Exiting...\n");
			exit(0);
		case SIGUSR1:
			syslog(LOG_NOTICE, "SIGUSR1\n");
			break;
		case SIGUSR2:
			syslog(LOG_NOTICE, "SIGUSR2\n");
			break;
                default:
                        break;
        }
}

void daemon_work(void)
{
	while(1) {
		
	}
}



int main(int argc, char** argv, char** env)
{
	pid_t pid;
	act_s.sa_handler = usr_sig_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act_s.sa_mask = set;
        sigaction(SIGINT, &act_s, NULL);
        sigaction(SIGUSR1, &act_s, NULL);
        sigaction(SIGUSR2, &act_s, NULL);

	switch(fork()) {
	case 0: /* child */
		setsid();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		pid = getpid();
		syslog(LOG_NOTICE, "Started cp1 with pid=%d. Wait signals...\n", pid);
		daemon_work();
		break;
	case -1: /* error */
		perror("fork");
		return -1;
	default: /* parent */
		return 0;
	}
	return 0;	
}


