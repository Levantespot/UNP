// Use Readn()
#include    "../lib/unpL.h"

void str_cli(FILE *fp, int sockfd);


int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in	servaddr;

    if (argc != 2)
		err_quit("usage: %s <IPaddress>\n", argv[0]);

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT); /* daytime server port */
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    Close(sockfd);

    return 0;
}

void str_cli(FILE *fp, int sockfd) {
    int maxfdp1;
    fd_set rset;
    char buf_send[MAXLINE], buf_recv[MAXLINE];
    int need_read_from_stdio = 1; // 1 for true, 0 for false
    int n; // bytes to read & write from socket

    FD_ZERO(&rset);
    for( ; ; ) {
        FD_SET(sockfd, &rset); // socket
        if (need_read_from_stdio) FD_SET(fileno(fp), &rset); // input

        maxfdp1 = (need_read_from_stdio) ? max(fileno(fp), sockfd) + 1 : sockfd +1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) { // socket is readable
            if ((n = Readn(sockfd, buf_recv, MAXLINE)) == 0) {
                if (need_read_from_stdio == 0) return; // normal termination
                else err_quit("str_cli: server terminated prematurely");
            }
            Writen(fileno(stdout), buf_recv, n);
        }

        if (FD_ISSET(fileno(fp), &rset)) { // input is readable
            if ((n = Readn(fileno(fp), buf_send, MAXLINE)) == 0) {
                // read EOF
                need_read_from_stdio = 0; // no longer needs to read from stdio
                Shutdown(sockfd, SHUT_WR); // no longer needs to write to socket
                FD_CLR(fileno(fp), &rset); // clear stdio in READFDS
                continue;
            }
            
            Writen(sockfd, buf_send, n);
        }
    }
}