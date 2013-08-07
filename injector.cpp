#include "injector.h"

#include <cstdio>

#include <Carbon/Carbon.h>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <dlfcn.h>

Injector::Injector()
{
}

Injector::~Injector()
{
}

void *Injector::pthread_entry(void *patch_bundle)
{
    void *bundle = dlopen((char *)patch_bundle, RTLD_NOW);
    if (!bundle)
        fprintf(stderr, "Could not load patch bundle: %s\n", dlerror());
    return 0;
}

void Injector::inject_entry(ptrdiff_t offset, void *param, size_t psize, void *dummy)
{
    __pthread_set_self(dummy);

    pthread_attr_t attr;
    pthread_attr_init(&attr); 
    
    int policy;
    pthread_attr_getschedpolicy(&attr, &policy);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    
    struct sched_param sched;
    sched.sched_priority = sched_get_priority_max(policy);
    pthread_attr_setschedparam(&attr, &sched);

    pthread_t thread;
    pthread_create(&thread, &attr,
            (void * (*)(void *))((long)pthread_entry),
            (void *)param);
    pthread_attr_destroy(&attr);
    
    thread_suspend(mach_thread_self());
}