#include "injector.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) return 0;

    char path[4096];
    realpath(argv[1], path);

    printf("%s\n", path);

    Injector inj;
    
    pid_t pid = inj.getProcessByName("testapp");
    printf("pid = %u\n", pid);

    inj.inject(pid, path);
    return 0;
}