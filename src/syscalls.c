/**
 * Dummy Syscall Implementations
 */

#include "main.h"

int _read(int fd, char *ptr, int len)
{
	return 0;
}

int _write(int fd, char *ptr, int len)
{
	return 0;
}

int _lseek(int fd, int ptr, int dir)
{
	return 0;
}

int _close(int fd)
{
	return 0;
}

int _getpid(void)
{
	return 0;
}

int _kill(int fd)
{
	return 0;
}

int _fstat(int fd, struct stat *st)
{
	return 0;
}

int _isatty(int fd)
{
	return 0;
}