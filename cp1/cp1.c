#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

bool usr1_en = 1;
int usr1_cnt = 0;
bool usr2_en = 1;
int usr2_cnt = 0;


sigset_t set; 
static struct sigaction act_s;
int port, sock, sock_accept;
struct sockaddr_in inaddr, fromaddr;
socklen_t sock_len = sizeof(fromaddr);

char buf_tcp_data[512];
const char help_str[] = {"usage: e1,e2,d1,d2,stop,info.\n"};

void usr_sig_handler(int sig)
{
        printf("sig = %d", sig);
        switch(sig) {
                case SIGINT:
			syslog(LOG_NOTICE, "Exiting...\n");
			exit(0);
		case SIGUSR1:
			syslog(LOG_NOTICE, "SIGUSR1\n");
			if(usr1_en) usr1_cnt++;
			break;
		case SIGUSR2:
			syslog(LOG_NOTICE, "SIGUSR2\n");
			if(usr2_en) usr2_cnt++;
			break;
                default:
                        break;
        }
}

void daemon_work(void)
{
	ssize_t ret;
	ret = send(sock_accept, help_str, strlen(help_str), 0);
	if(ret < 0) syslog(LOG_NOTICE, "Errorr while send data!\n");

	while(1) {
		ret = recv(sock_accept, buf_tcp_data, sizeof(buf_tcp_data), 0);
		if(ret > 0) {
			syslog(LOG_NOTICE, "Received data %s\n", buf_tcp_data);
			buf_tcp_data[ret]=0;

			if(!strncmp(buf_tcp_data, "e1", 2)) {
				ret = snprintf(buf_tcp_data, sizeof(buf_tcp_data), "%s\n", "enable usr1 counter");
				send(sock_accept, buf_tcp_data, ret, 0);
				usr1_en = 1;
			} else if(!strncmp(buf_tcp_data, "e2", 2)) {
				ret = snprintf(buf_tcp_data, sizeof(buf_tcp_data), "%s\n", "enable usr2 counter");
				send(sock_accept, buf_tcp_data, ret, 0);
				usr2_en = 1;
			} else if(!strncmp(buf_tcp_data, "d1", 2)) {
				ret = snprintf(buf_tcp_data, sizeof(buf_tcp_data), "%s\n", "disable usr1 counter");
				send(sock_accept, buf_tcp_data, ret, 0);
				usr1_en = 0;
			} else if(!strncmp(buf_tcp_data, "d2", 2)) {
				ret = snprintf(buf_tcp_data, sizeof(buf_tcp_data), "%s\n", "disable usr2 counter");
				send(sock_accept, buf_tcp_data, ret, 0);
				usr2_en = 0;
			} else if(!strncmp(buf_tcp_data, "info", 4)) {
				ret = snprintf(buf_tcp_data,
				sizeof(buf_tcp_data), "usr1 count=%d, usr2 count=%d\n", usr1_cnt, usr2_cnt);
				send( sock_accept, buf_tcp_data, ret, 0 );
			} else if(!strncmp(buf_tcp_data, "stop", 4)) {
				send(sock_accept, "bye...\n", strlen("bye...\n"), 0);
				break;
			} else
				send(sock_accept, help_str, strlen(help_str), 0);
		} else
		if(ret == 0) {
			continue;
		} else if(ret < 0) {
			syslog(LOG_DEBUG, "Error receive data with code %d.\n", (int)ret);
			continue;
		}
	}
	syslog(LOG_NOTICE, "Exit. ret <= 0!\n");
}



int main(int argc, char** argv, char** env)
{
	pid_t pid;


	if(argc != 2) {
		printf("usage:\t%s порт\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);
	if(port > 65000) {
		printf("error port \"%s\"\tPort must be <= 65000\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	act_s.sa_handler = usr_sig_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act_s.sa_mask = set;
        sigaction(SIGINT, &act_s, NULL);
        sigaction(SIGUSR1, &act_s, NULL);
        sigaction(SIGUSR2, &act_s, NULL);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = htonl((in_addr_t) INADDR_ANY);
	inaddr.sin_port = htons(port);
	printf("\nbind to inaddr....");
	if( bind(sock, (struct sockaddr*)&inaddr, sizeof(inaddr)) < 0) {
		perror("bind inaddr");
		puts("failure!");
		exit(EXIT_FAILURE);
	}
	printf("success!\nListen sock...");
	if(listen(sock, 10) < 0) {
		puts("listen errorr!");
		exit(EXIT_FAILURE);
	}
	printf("success listen sock init!\naccept socket...");

	sock_accept = accept(sock, (struct sockaddr*)(&fromaddr), &sock_len);
	if( sock_accept <= 0) {
		puts("Accept sock error!");
		exit(EXIT_FAILURE);
	}
	puts("Accept success");
	switch(fork()) {
	case 0: /* child */
		setsid();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		pid = getpid();
		openlog("cp1", 0, LOG_USER);
		syslog(LOG_NOTICE, "Started cp1 with pid=%d. Wait signals...\n", pid);
		daemon_work();
		break;
	case -1: /* error */
		perror("fork");
		return -1;
	default: /* parent */
		return 0;
	}
	exit(EXIT_FAILURE);	
}


