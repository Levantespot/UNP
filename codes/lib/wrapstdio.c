/*
 * Standard I/O wrapper functions in stdio.h
 */

#include	"unpL.h"

void Fclose(FILE *fp)
{
	if (fclose(fp) != 0)
		err_sys("fclose error");
}

FILE *Fdopen(int fd, const char *type)
{
	FILE	*fp;

	if ( (fp = fdopen(fd, type)) == NULL)
		err_sys("fdopen error");

	return(fp);
}

// return NULL if reads EOF, else return ptr;
char *Fgets(char *ptr, int n, FILE *stream)
{
	char	*rptr;
    // fgets return NULL if reads EOF or find ERROR
	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		err_sys("fgets error");

	return (rptr);
}

FILE *Fopen(const char *filename, const char *mode)
{
	FILE	*fp;

	if ( (fp = fopen(filename, mode)) == NULL)
		err_sys("fopen error");

	return(fp);
}

void Fputs(const char *ptr, FILE *stream)
{
	if (fputs(ptr, stream) == EOF)
		err_sys("fputs error");
}
