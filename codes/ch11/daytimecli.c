#include    "../lib/unpL.h"

int main(int argc, char **argv) {
	int					sockfd, n;
	char				recvline[MAXLINE + 1]; // buffer
	struct sockaddr_storage	servaddr;
    socklen_t addrlen = sizeof(servaddr);

    if (argc != 3)
		err_quit("usage: %s <Hostname/IPaddress> <service/port#>\n", argv[0]);

    sockfd = Tcp_connect(argv[1], argv[2]);

    Getpeername(sockfd, (SA *)&servaddr, &addrlen);

    printf("Connneted to %s\n", sock_ntop((SA *) &servaddr, addrlen));

    while ( (n = Readn(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        Fputs(recvline, stdout);
	}

    printf("Disconnected from %s\n", sock_ntop((SA *) &servaddr, addrlen));

	if (n < 0)
		err_sys("read error");

    return 0;
}