#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

#include "ft_printf.h"

int capture_stdout(char **buffer, int (*print_func)(const char *format, ...), const char *format, ...) {
    int stdout_cp = dup(STDOUT_FILENO);
    int pipefd[2];
    va_list args;
    int nb;

    if (pipe(pipefd) == -1)
        return -1;

    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    va_start(args, format);
    nb = print_func(format, args);
    va_end(args);

    fflush(stdout);
    dup2(stdout_cp, STDOUT_FILENO);
    close(stdout_cp);

    *buffer = malloc(1024);
    if (!*buffer)
        return -1;

    nb = read(pipefd[0], *buffer, 1023);
    (*buffer)[nb] = '\0';
    close(pipefd[0]);

    return nb;
}

int	main(void) 
{
    char	*buffer_1;
    char	*buffer_2;
    int		nb_1;
    int		nb_2;

    nb_2 = capture_stdout(&buffer_2, printf, "hello worlddd%s", " hello");
    nb_1 = capture_stdout(&buffer_1, ft_printf, "hello world%s", " hello");

    if (!strcmp(buffer_1, buffer_2)) {
        printf("Working correct\n");
    } else {
        printf("nop\n");
    }

    free(buffer_1);
    free(buffer_2);
    
    return 0;
}
