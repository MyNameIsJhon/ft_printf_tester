#include <stdlib.h>
#include "print_test.h"

int test_empty_string(void)
{
    char *buf_std, *buf_ft;
    int ret_std, ret_ft;

    ret_std = capture_stdout(&buf_std, printf, "");
    ret_ft  = capture_stdout(&buf_ft,  ft_printf, "");

    if (ret_std != ret_ft || strcmp(buf_std, buf_ft) != 0)
    {
        printf("Error [test_empty_string]: expected return %d and output \"%s\", but got return %d and output \"%s\"\n",
               ret_std, buf_std, ret_ft, buf_ft);
        free(buf_std);
        free(buf_ft);
        return 0;
    }
	
    free(buf_std);
    free(buf_ft);
    return 1;
}

int test_simple_string(void)
{
    char *buf_std, *buf_ft;
    int ret_std, ret_ft;

    ret_std = capture_stdout(&buf_std, printf, "Hello, world!\n");
    ret_ft  = capture_stdout(&buf_ft,  ft_printf, "Hello, world!\n");

    if (ret_std != ret_ft || strcmp(buf_std, buf_ft) != 0)
    {
        printf("Error [test_simple_string]: expected return %d and output \"%s\", but got return %d and output \"%s\"\n",
               ret_std, buf_std, ret_ft, buf_ft);
        free(buf_std);
        free(buf_ft);
        return 0;
    }

    free(buf_std);
    free(buf_ft);
    return 1;
}

int test_literal_percent(void)
{
    char *buf_std, *buf_ft;
    int ret_std, ret_ft;

    ret_std = capture_stdout(&buf_std, printf, "%%");
    ret_ft  = capture_stdout(&buf_ft,  ft_printf, "%%");

    if (ret_std != ret_ft || strcmp(buf_std, buf_ft) != 0)
    {
        printf("Error [test_literal_percent]: expected return %d and output \"%s\", but got return %d and output \"%s\"\n",
               ret_std, buf_std, ret_ft, buf_ft);
        free(buf_std);
        free(buf_ft);
        return 0;
    }

    free(buf_std);
    free(buf_ft);
    return 1;
}

int test_percent_in_text(void)
{
    char *buf_std, *buf_ft;
    int ret_std, ret_ft;

    ret_std = capture_stdout(&buf_std, printf, "Progress: 100%% complete\n");
    ret_ft  = capture_stdout(&buf_ft,  ft_printf, "Progress: 100%% complete\n");

    if (ret_std != ret_ft || strcmp(buf_std, buf_ft) != 0)
    {
        printf("Error [test_percent_in_text]: expected return %d and output \"%s\", but got return %d and output \"%s\"\n",
               ret_std, buf_std, ret_ft, buf_ft);
        free(buf_std);
        free(buf_ft);
        return 0;
    }

    free(buf_std);
    free(buf_ft);
    return 1;
}

void run_global_tests(void)
{
    printf("Running global tests:\n");
    int all_ok = 1;

    all_ok &= test_empty_string();
    all_ok &= test_simple_string();
    all_ok &= test_literal_percent();
    all_ok &= test_percent_in_text();

    if (all_ok)
        printf("✔ All global tests passed\n");
    else
        printf("✘ Some global tests failed\n");
}
