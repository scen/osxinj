#include <cstdio>

void install(void) __attribute__ ((constructor));

void install()
{
    printf("hello, world!\n");
}