#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include <mach_inject/mach_inject.h>
#include <Carbon/Carbon.h>

extern "C" void __pthread_set_self(void*);

class Injector
{
private:
    static void *pthread_entry(void *patch_bundle);
    static void inject_entry(ptrdiff_t offset, void *param, size_t psize, void *dummy);
public:
    Injector();
    ~Injector();

    OSErr getProcessByName(OSType type, StringPtr name, ProcessSerialNumber &psn);
};

#endif