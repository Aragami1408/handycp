#ifndef MTHREADS_H
#define MTHREADS_H

#include "dbg.h"

#ifndef MTHREAD_MODE
#define MTHREAD_MODE
#endif

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct Mutex {
    pthread_mutex_t mutex;
    pthread_t owner;
    int count;
} Mutex;

#define MTX_NEW(m,r)                                                            \
    do {                                                                        \
        Mutex *x = (Mutex *) calloc(1, sizeof(Mutex));                          \
        pthread_mutexattr_t _mtxattr;                                           \
        pthread_mutexattr_init(&_mtxattr);                                      \
        if (r) {                                                                \
            pthread_mutexattr_settype(&_mtxattr, PTHREAD_MUTEX_RECURSIVE);      \
        }                                                                       \
        int _ret = pthread_mutex_init(&(x->mutex), &_mtxattr);              	\
        pthread_mutexattr_destroy(&_mtxattr);                                   \
        if (_ret == 0) {                                                        \
            m = x;                                                              \
        }                                                                       \
        else {                                                                  \
            DEBUG("MTX: can't initialize mutex. [%d]", _ret);                   \
            free(x);                                                            \
            m = NULL;                                                           \
        }                                                                       \
    } while(0)

#define MTX_LEAVE(m)                                        \
    do {                                                    \
        if (m == NULL) break;                               \
        Mutex *x = (Mutex *)m;                              \
        if (!pthread_equal(x->owner, pthread_self())) {     \
            DEBUG("MTX: unlock - owner mismatch.");         \
        }                                                   \
        if ((x->count--) < 0) x->count = 0;                 \
        pthread_mutex_unlock(&(x->mutex));                  \
    } while(0)                                                                                      

#define MAX_MTX_LOCK_WAIT (5000)
#define MTX_ENTER(m)                                                                                        \
    do {                                                                                                    \
        if (m == NULL) break;                                                                               \
        Mutex *x = (Mutex *)m;                                                                              \
        while(true) {                                                                                       \
            int _ret, i;                                                                                    \
            for (i = 0; (_ret = pthread_mutex_trylock(&(x->mutex))) != 0 && i < MAX_MTX_LOCK_WAIT; i++) {   \
                if (i == 0) {                                                                               \
                    DEBUG("MTX: mutex is already locked - retrying");                                       \
                }                                                                                           \
                usleep(1);                                                                                  \
            }                                                                                               \
            if (_ret == 0) break;                                                                           \
            DEBUG("MTX: can't get lock - force to unlock. [%d]", _ret);                                     \
            MTX_LEAVE(x);                                                                                   \
        }                                                                                                   \
        x->count++;                                                                                         \
        x->owner = pthread_self();                                                                          \
    } while(0)

#define MTX_DESTROY(m)                                              \
    do {                                                            \
        if (m == NULL) break;                                        \
        Mutex *x = (Mutex *)m;                                      \
        if (x->count != 0) DEBUG("MTX: mutex counter is not 0.");   \
        int _ret;                                                    \
        while((_ret = pthread_mutex_destroy(&(x->mutex))) != 0) {   \
            DEBUG("MTX: force to unlock mutex. [%d]", _ret);        \
            MTX_LEAVE(x);                                           \
        }                                                           \
        free(x);                                                    \
    } while(0)  



#endif
