#include "Container.h"

Container newContainer(Container c){
    Container res = c;

    res.object = res.new();

    return res;
}

int setFreeCallBackContainer(Container c, void (*Free)(void *)){
    return c.free_callback(c.object,Free);
}

void deleteContainer(Container c){
    c.delete(c.object);
}

int pushBackContainer(Container c, void * v){
    return c.pushBack(c.object,v);
}

int pushFrontContainer(Container c, void * v){
    return c.pushFront(c.object,v);
}

void * popBackContainer(Container c){
    return c.popBack(c.object);
}

void * popFrontContainer(Container c){
    return c.popFront(c.object);
}

size_t lenContainer(Container c){
    return c.len(c.object);
}

void * getContainer(Container c,size_t id){
    return c.get(c.object,id);
}

void * setContainer(Container c,size_t id,void * v){
    return c.set(c.object,id,v);
}
