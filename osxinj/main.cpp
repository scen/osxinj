#include "injector.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./osxinj [proc_name] [lib]\n");
        return -1;
    }
    
    if (getuid() > 0) {
        fprintf(stderr, "please run me as root\n");
        return -1;
    }

    char path[4096];
    realpath(argv[2], path);

    fprintf(stderr, "%s\n", path);

    Injector inj;
    
    pid_t pid = inj.getProcessByName(argv[1]);
    if (!pid)
    {
        fprintf(stderr, "process %s not found\n", argv[1]);
        return 0;
    }
    fprintf(stderr, "pid: %u\n", pid);
    
    inj.inject(pid, path);
    return 0;
}