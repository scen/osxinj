#include "injector.h"

#include <cstdio>
#include <cstring>

#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <dlfcn.h>
#include <signal.h>
#include <sys/proc_info.h>
#include <libproc.h>    

Injector::Injector()
{
}

Injector::~Injector()
{
}

void Injector::inject(pid_t pid, const char* lib)
{
    mach_error_t err = mach_inject(&Injector::inject_entry, lib, sizeof(lib) + 1, pid, 0);
}

pid_t Injector::getProcessByName(const char *name)
{
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));

    for (int i = 0; i < procCnt; i++)
    {
        if (!pids[i]) continue;
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        int len = strlen(curPath);
        if (len)
        {
            int pos = len;
            while (pos && curPath[pos] != '/') --pos;
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name))
            {
                return pids[i];
            }
        }
    }
    return 0;
}

void *Injector::pthread_entry(void *patch_bundle)
{
    // printf("str = %s\n", (char*)patch_bundle);
    // void *bundle = dlopen((char *)patch_bundle, RTLD_NOW);
    // if (!bundle)
    //     fprintf(stderr, "Could not load patch bundle: %s\n", dlerror());
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