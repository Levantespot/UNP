#include    "../lib/unpL.h"
#include    "sigchldwait.c"

void str_echo(int sockfd);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr, cliaddr;
	
	socklen_t cli_salen;
    pid_t pid;
    

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(SERVER_PORT);	/* daytime server */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
    signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
        cli_salen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (SA *)&cliaddr, &cli_salen)) < 0) { // use original accept()
            if (errno == EINTR) continue; // handler for EINTR
            else err_sys("accept error");
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error!");
        } else if (pid == 0) { // child process
            Close(listenfd);
            str_echo(connfd);
            // Close(connfd);
            return 0;
        }
		Close(connfd);
	}
    return 0;
}

void str_echo(int sockfd) {
    char buff[MAXLINE];
    ssize_t n; // returned number by Readline()

again:
    while ((n = Readline(sockfd, buff, MAXLINE)) > 0) {
        Writen(sockfd, buff, strlen(buff));
    }
    if (n < 0 && errno == EINTR) goto again;
    else if (n < 0) err_sys("str_echo : read error!\n");
}