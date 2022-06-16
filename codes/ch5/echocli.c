#include    "../lib/unpL.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv) {
	int					sockfd;
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

    return 0;
}

void str_cli(FILE *fp, int sockfd) {
    char buf_send[MAXLINE], buf_recv[MAXLINE];
    while (Fgets(buf_send, MAXLINE, fp) != NULL) {
        Writen(sockfd, buf_send, strlen(buf_send));
        if (Readline(sockfd, buf_recv, MAXLINE) > 0) {
            Fputs(buf_recv, stdout);
        } else {
            err_sys("str_cli: Readline() error!");
        }
    }
}