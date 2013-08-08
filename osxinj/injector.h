#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include "mach_inject.h"

class Injector
{
public:
    Injector();
    ~Injector();

    void inject(pid_t pid, const char* lib);
    pid_t getProcessByName(const char *name);
private:
    void *module;
    void *bootstrapfn;
};

#endif