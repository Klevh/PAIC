#ifndef _MAIN_CONTAINER_KLEVH_
#define _MAIN_CONTAINER_KLEVH_

#include <stdlib.h>

typedef struct{
    void * object;
    void * (*new)(void);
    int (*free_callback)(void *,void (*Free)(void*));
    void (*delete)(void *);
    int (*pushBack)(void *, void *);
    int (*pushFront)(void *, void *);
    void * (*popBack)(void *);
    void * (*popFront)(void *);
    size_t (*len)(void *);
    void * (*get)(void *, size_t);
    void * (*set)(void *, size_t,void*);
}Container;

Container newContainer(Container);
int setFreeCallBackContainer(Container,void(*)(void*));
void deleteContainer(Container);
int pushBackContainer(Container,void *);
int pushFrontContainer(Container,void *);
void * popBackContainer(Container);
void * popFrontContainer(Container);
size_t lenContainer(Container);
void * getContainer(Container,size_t);
void * setContainer(Container,size_t,void *);

#endif
