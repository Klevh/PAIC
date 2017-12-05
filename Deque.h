#ifndef _DEQUE_BY_KLEVH_
#define _DEQUE_BY_KLEVH_

#include <stdlib.h>
#include "Container.h"

typedef void * deque_t;

deque_t newDeque();
void deleteDeque(deque_t l);
int pushBackDeque(deque_t l, void * value);
int pushFrontDeque(deque_t l,void * value);
void * popBackDeque(deque_t l);
void * popFrontDeque(deque_t l);
void * setDeque(deque_t l, unsigned long id, void * value);
void * getDeque(deque_t l, unsigned long id);
int initIteratorFrontDeque(deque_t l);
int initIteratorBackDeque(deque_t l);
void * nextIteratorDeque(deque_t l,int * error);
void * prevIteratorDeque(deque_t l,int * error);
void * getCurrentDeque(deque_t l,int * error);
unsigned long lenDeque(deque_t l);
int setFreeCallBackDeque(deque_t l,void (*yourFree)(void *));

extern const Container Deque;

#endif
