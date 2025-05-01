#ifndef PRINT_TEST_H
# define PRINT_TEST_H

void run_global_tests(void);
int capture_stdout(char **buffer, int (*print_func)(const char *format, ...), const char *format, ...) ;

#endif
