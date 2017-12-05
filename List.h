#ifndef _LIST_BY_KLEVH_
#define _LIST_BY_KLEVH_

#include <stdlib.h>
#include "Container.h"

typedef void * list_t;

list_t newList();
void deleteList(list_t l);
int pushBackList(list_t l, void * value);
int pushFrontList(list_t l,void * value);
void * popBackList(list_t l);
void * popFrontList(list_t l);
int pushList(list_t l,unsigned long id,void* value);
void * popList(list_t l,unsigned long id);
void * setList(list_t l, unsigned long id, void * value);
void * getList(list_t l, unsigned long id);
int initIteratorFrontList(list_t l);
int initIteratorBackList(list_t l);
void * nextIteratorList(list_t l,int * error);
void * prevIteratorList(list_t l,int * error);
unsigned long lenList(list_t l);
int setFreeCallBackList(list_t l,void (*yourFree)(void*));

extern const Container List;

#endif
