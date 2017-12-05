#ifndef _VECTOR_BY_KLEVH_
#define _VECTOR_BY_KLEVH_

#include <stdlib.h>
#include "Container.h"

typedef void * vector_t;
	
vector_t newVector();
int setFreeCallBackVector(vector_t v,void (*yourFree)(void *));
void deleteVector(vector_t v);
int pushBackVector(vector_t v, void * value);
int pushFrontVector(vector_t v, void* value);
void * popBackVector(vector_t v);
void * popFrontVector(vector_t v);
int initIteratorFrontVector(vector_t v);
void * nextIteratorVector(vector_t v,int * error);
int initIteratorBackVector(vector_t v);
void * prevIteratorVector(vector_t v,int * error);
unsigned long lenVector(vector_t v);
void * getVector(vector_t v,unsigned long id);
void * setVector(vector_t v, unsigned long id,void * value);

extern const Container Vector;

#endif
