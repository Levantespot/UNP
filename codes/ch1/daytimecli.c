#include    "../lib/unpL.h"

int main(int argc, char **argv) {
	int					sockfd, n;
	char				recvline[MAXLINE + 1]; // buffer
	struct sockaddr_in	servaddr;

    if (argc != 2)
		err_quit("usage: %s <IPaddress>\n", argv[0]);

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT); /* daytime server port */
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) /* daytime server ip */
		err_quit("inet_pton error for %s", argv[1]);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    printf("Connneted to %s\n", sock_ntop((SA *) &servaddr, sizeof(servaddr)));

    while ( (n = Readline(sockfd, recvline, MAXLINE)) > 0) {
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}

    printf("Disconnected from %s\n", sock_ntop((SA *) &servaddr, sizeof(servaddr)));

	if (n < 0)
		err_sys("read error");

    return 0;
}