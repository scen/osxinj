#include "injector.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <dlfcn.h>

int main(int argc, char* argv[])
{
    void *module = dlopen("/Users/scen/projects/osxinj/bootstrap/bootstrap.dylib", 
        RTLD_NOW | RTLD_LOCAL);

    if (!module)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 0;
    }

    void *bootstrapfn = dlsym(module, "bootstrap");
    printf("bootstrapfn: 0x%X\n", bootstrapfn);

    if (!bootstrapfn)
    {
        fprintf(stderr, "could not locate boostrap fn\n");
        return 0;
    }
    Injector inj;
    
    pid_t pid = inj.getProcessByName("testapp");
    printf("pid = %u\n", pid);

    mach_inject((mach_inject_entry)bootstrapfn, "Helloworld", strlen("Helloworld") + 1, pid, 0);

    // inj.inject(pid, "test");
    return 0;
}