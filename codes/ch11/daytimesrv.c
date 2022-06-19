#include    "../lib/unpL.h"
#include	<time.h>

void sig_chld(int signo) {
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
    }
    
    return;
}

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	char				buff[MAXLINE];
	time_t				ticks;
    pid_t               pid;

    if (argc != 2)
		err_quit("usage: %s <service/port#>\n", argv[0], argv[1]);

	listenfd = Tcp_listen(NULL, argv[1], NULL);
    signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *)NULL, NULL);
        if ((pid = fork()) < 0) {
            err_sys("fork error!");
        } else if (pid == 0) {
            Close(listenfd);
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "pid = %d, %s\n", getpid(), ctime(&ticks));
            Writen(connfd, buff, strlen(buff));
            Close(connfd);
            return 0;
        }
		Close(connfd); // close eventually until child process close it
	}
    Close(listenfd);
    return 0;
}
