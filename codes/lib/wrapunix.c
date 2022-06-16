#include	"unpL.h"

void *Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

void Dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		err_sys("dup2 error");
}

int Fcntl(int fd, int cmd, int arg)
{
	int	n;

	if ( (n = fcntl(fd, cmd, arg)) == -1)
		err_sys("fcntl error");
	return(n);
}

pid_t Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return(pid);
}

void * Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

void Unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
		err_sys("unlink error for %s", pathname);
}

pid_t Wait(int *iptr)
{
	pid_t	pid;

	if ( (pid = wait(iptr)) == -1)
		err_sys("wait error");
	return(pid);
}

pid_t Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t	retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");
	return(retpid);
}

// void Write(int fd, void *ptr, size_t nbytes)
// {
// 	if (write(fd, ptr, nbytes) != nbytes)
// 		err_sys("write error");
// }
