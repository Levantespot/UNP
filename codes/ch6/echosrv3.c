// Single process version using select()
// Use Readn()
#include    "../lib/unpL.h"

void str_echo(int sockfd);

int main(int argc, char **argv)
{
	int i, maxfd, listenfd, connfd, sockfd;
    int maxi;   // max index in clients[].
                // Use it to reduce loop times when finding avaliable position in clients[]
	struct sockaddr_in servaddr, cliaddr;
	socklen_t cli_salen;
    fd_set rset, next_rset;
    int nready, clients[FD_SETSIZE];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(SERVER_PORT);	/* daytime server */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

    maxfd = listenfd;
    maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++) clients[i] = -1;
    FD_ZERO(&next_rset);
    FD_SET(listenfd, &next_rset);
    for ( ; ; ){
        rset = next_rset; // == FD_SET(listenfd, &rset);
        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset)) {
            cli_salen = sizeof(cli_salen);
            connfd = Accept(listenfd, (SA *)&cliaddr, &cli_salen);

            // find an avaliable location in clients[] for connfd
            for (i = 0; i < FD_SETSIZE; i++) {
                if (clients[i] == -1) {
                    clients[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE) err_quit("too many clients");
            FD_SET(connfd, &next_rset);
            maxi = (i > maxi) ? i : maxi;
            maxfd = (connfd > maxfd) ? connfd : maxfd;
            
            if (--nready <= 0) continue; // no more readable descriptors
        }

        for (i = 0; i <= maxi; i++) {
            if ((sockfd = clients[i]) < 0) continue;
            if (FD_ISSET(sockfd, &rset)) {
                str_echo(sockfd);
                Close(sockfd);
                FD_CLR(sockfd, &next_rset);
                clients[i] = -1; // avaliable for next client

                if (--nready <= 0) break; // no more readable descriptors
            }
        }
        
    }
    
    Close(listenfd);
    return 0;
}

void str_echo(int sockfd) {
    char buf[MAXLINE];
    ssize_t n; // returned number by Readn()

again:
    while ((n = Readn(sockfd, buf, MAXLINE)) > 0) {
        Fputs(buf, stdout);
        Writen(sockfd, buf, n);
    }
    if (n < 0 && errno == EINTR) goto again;
    else if (n < 0) err_sys("str_echo : read error!\n");
    else if (n == 0) printf("(Recieved an EOF.)\n");
}