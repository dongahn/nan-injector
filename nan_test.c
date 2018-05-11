#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    double *test_array = malloc (4096 * sizeof (*test_array));

    // use of unitialized variable
    double var = test_array[512] * test_array[1024];
    printf ("%lf\n", var);
    return 0;
}
