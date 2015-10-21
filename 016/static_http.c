#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 32768

int cancel = 0;

void my_signal_handler(int sig)
{
//	printf("sig = %d", sig);
	switch(sig) {
		case SIGINT:
			puts("Exiting...");
			cancel = 1;
		default:
			break;
	}
}


int main(int argc, char** argv, char** env)
{
	int port, sock, sock_accept;
	struct sockaddr_in inaddr;
	struct sockaddr_in fromaddr;
	socklen_t soc_len = sizeof(fromaddr);
	char buf[BUF_SIZE];

	static struct sigaction act_s;
	if(argc != 2) {
		printf("usage:\t%s порт\n", argv[0]);
		return 1;
	}
	port = atoi(argv[1]);

	if(port>65000){
		perror("argv[1]");
		exit(EXIT_FAILURE);
	}
	act_s.sa_handler = my_signal_handler;
	sigaction(SIGINT, &act_s, NULL);
	
	sock=socket(AF_INET, SOCK_STREAM, 0);

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
	puts("success!");
	if(listen(sock, 10) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	FILE* fd_htm = fopen("index.html", "r");
	FILE* fd_img = fopen("my_image.png", "r");
	if((fd_htm < 0) || (fd_img < 0)) {
		perror("open_data");
		exit(EXIT_FAILURE);
	}

	fseek(fd_htm, 0, SEEK_END);
	long fdsize = ftell(fd_htm);

	fseek(fd_img, 0, SEEK_END);
	long fd1size = ftell(fd_img);


	while(!cancel) {
		sock_accept = accept(sock, (struct sockaddr*)(&fromaddr), &soc_len);
		int nb = recv(sock_accept, buf, BUF_SIZE, 0);
		if (nb <= 0)	break;
		buf[nb] = 0;
		printf("http request: %s", buf);
		
		
		char str[120];
		sscanf(buf, "%s %s", str, str + 1);

		char* to = str+1;
		if(strlen(to) == 0)	to="index.html";
		else if (strcmp(str+1, "/my_image.jpg\0") == 0) {
			to="my_image.png";
		}

		if(access(to, F_OK) == -1) {
			to = buf;
			to=stpcpy(to, "HTTP/1.1 404 Not Found\n");
			to=stpcpy(to, "Connection: keep-alive\n");
			to=stpcpy(to, "Content-Type: text/html; charset=UTF-8\n");
			to=stpcpy(to, "Keep-Alive: timeout=5,max=97\n");
			to=stpcpy(to, "\n");
			to=stpcpy(to, "Erorr 404 Page not found\n");
		} else {
			int n = strcmp(to, "my_image.png");
			if(n == 0) {
				to = buf;
				fseek(fd_img, 0, SEEK_SET);
				to = stpcpy(to, "HTTP/1.1 200 OK\n");
				to = stpcpy(to, "Connection: keep-alive\n");
				to = stpcpy(to, "Content-Type: image/jpeg\n");
				to = stpcpy(to, "Keep-Alive: timeout=5,max=97\n");
				to = stpcpy(to, "\n");
				nb = fread (to, fd1size, 1, fd_img);
				if (nb <= 0) break;
				to += fd1size;
			} else {
				to = buf;
				fseek(fd_htm, 0, SEEK_SET);
				to = stpcpy(to, "HTTP/1.1 200 OK\n");
				to = stpcpy(to, "Connection: keep-alive\n");
				to = stpcpy(to, "Content-Type: text/html; charset=UTF-8\n");
				to = stpcpy(to, "Keep-Alive: timeout=5,max=97\n");
				to = stpcpy(to, "\n");
				nb = fread (to, fdsize, 1, fd_htm);
				if (nb <= 0) break;
				to += fdsize;
			}
		}
		to = stpcpy(to, "\n");

		send(sock_accept, buf, to-buf, 0);
		printf("Send: %s", buf);




		close(sock_accept);
	}
	fclose(fd_htm);
	fclose(fd_img);
	close(sock);
	return 0;
}
