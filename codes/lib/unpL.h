/* 
 * A light Unix network programming library by Levante. (self-use)
 */

#ifndef	_UNP_L
#define _UNP_L 1

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>
#include	<errno.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <sys/wait.h>
#include    <signal.h>
#include    <sys/select.h>
#include    <sys/poll.h>
#include    <limits.h>

#define	LISTENQ		1024	/* 2nd argument to listen() */
#define SERVER_PORT 7123    /* used port */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

#define	SA	struct sockaddr

/* Some useful calculations */
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define min(a, b) ((a) < (b)) ? (a) : (b)

/* in wrapsocket.c  */
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr);
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);
void Listen(int fd, int backlog);
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags);
ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		 struct sockaddr *sa, socklen_t *salenptr);
ssize_t Recvmsg(int fd, struct msghdr *msg, int flags);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout);
void Send(int fd, const void *ptr, size_t nbytes, int flags);
void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
	   const struct sockaddr *sa, socklen_t salen);
void Sendmsg(int fd, const struct msghdr *msg, int flags);
void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
void Shutdown(int fd, int how);
int Sockatmark(int fd);
int Socket(int family, int type, int protocol);
void Socketpair(int family, int type, int protocol, int *fd);
char *sock_ntop(const struct sockaddr *sa, socklen_t salen);


/* in wrapunix.c  */
void *Calloc(size_t n, size_t size);
void Close(int fd);
void Dup2(int fd1, int fd2);
int Fcntl(int fd, int cmd, int arg);
pid_t Fork(void);
void * Malloc(size_t size);
void Unlink(const char *pathname);
pid_t Wait(int *iptr);
pid_t Waitpid(pid_t pid, int *iptr, int options);
// void Write(int fd, void *ptr, size_t nbytes);

/* in error.c  */
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

/* in wrapio.c  */
ssize_t Readn(int fd, void *ptr, size_t nbytes);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
void Writen(int fd, void *ptr, size_t nbytes);

/* in wrapstdio.c  */
void Fclose(FILE *fp);
FILE *Fdopen(int fd, const char *type);
char *Fgets(char *ptr, int n, FILE *stream);
FILE *Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);

#endif	/* _UNP_L */