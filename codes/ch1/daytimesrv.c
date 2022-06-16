#include    "../lib/unpL.h"
#include	<time.h>

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
    // socklen_t           salenptr;
	char				buff[MAXLINE];
	time_t				ticks;
    pid_t               pid;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(SERVER_PORT);	/* daytime server */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *)NULL, NULL);
        if ((pid = fork()) < 0) {
            err_sys("fork error!");
        } else if (pid > 0) { // parent process
            Close(listenfd);
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "pid = %d, %s\n", getpid(), ctime(&ticks));
            Writen(connfd, buff, strlen(buff));
            Close(connfd);
            return 0;
        }
		Close(connfd);
	}

    return 0;
}
