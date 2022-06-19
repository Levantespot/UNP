// Single process version using poll()
// Use Readline()
#include    "../lib/unpL.h"

void str_echo(int sockfd);

int main(int argc, char **argv)
{
	int i, maxi, listenfd, connfd, sockfd;
    int nready;
	socklen_t cli_salen;
    struct pollfd clients[FOPEN_MAX];
    struct sockaddr_in servaddr, cliaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(SERVER_PORT);	/* daytime server */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

    clients[0].fd = listenfd;
    clients[0].events = POLLIN;
    for (i = 1; i < FOPEN_MAX; i++) clients[i].fd = -1;
    maxi = 0;
    for ( ; ; ){
        nready = Poll(clients, maxi+1, -1);
        if (clients[0].revents & POLLIN) {
            cli_salen = sizeof(cli_salen);
            connfd = Accept(listenfd, (SA *)&cliaddr, &cli_salen);

            // find an avaliable location in clients[] for connfd
            for (i = 0; i < FOPEN_MAX; i++) {
                if (clients[i].fd < 0) {
                    clients[i].fd = connfd;
                    break;
                }
            }
            if (i == FOPEN_MAX) err_quit("too many clients");
            clients[i].events = POLLIN;
            maxi = (i > maxi) ? i : maxi;
            
            if (--nready <= 0) continue; // no more readable descriptors
        }

        for (i = 0; i <= maxi; i++) {
            if ((sockfd = clients[i].fd) < 0) continue;
            if (clients[i].revents & (POLLIN | POLLERR)) {
                str_echo(sockfd);
                Close(sockfd);
                
                clients[i].fd = -1; // avaliable for next client

                if (--nready <= 0) break; // no more readable descriptors
            }
        }
        
    }
    
    Close(listenfd);
    return 0;
}

void str_echo(int sockfd) {
    char buf[MAXLINE];
    ssize_t n; // returned number by Readline()

again:
    while ((n = Readline(sockfd, buf, MAXLINE)) > 0) {
        Fputs(buf, stdout);
        Writen(sockfd, buf, n);
    }
    if (n < 0 && errno == EINTR) goto again;
    else if (n < 0) err_sys("str_echo : read error!\n");
    else if (n == 0) printf("(Recieved an EOF.)\n");
}