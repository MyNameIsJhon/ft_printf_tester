#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>

char	*capture_stdout(int (*func)(), char **buffer, const char *format, ...)
{

	int		stdout_cp = dup(STDOUT_FILEND);
	int		pipefd[2];
	va_list	args;
	int		nb;

	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	va_start(args, format);
	func(format, args);
	va_end(args);

	fflush(stdout);
	
	dup2(stdout_cp, STDOUT_FILENO);
	close(stdout_cp);
	
	if (!(*buffer = (char *)malloc(1024)))
		return (NULL);
	nb = read(pipefd[0], buffer, 1023);
	close(pipefd[0]);
}

int main(void)
{

}
