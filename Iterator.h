#ifndef _ITERATOR_BY_KLEVH_
#define _ITERATOR_BY_KLEVH_

#include <stdlib.h>

typedef void * Iterator;
typedef void * FunctionIterator;

typedef enum IT_BOOL{
  IT_FALSE,
  IT_TRUE
}IT_BOOL;

/* FunctionIterator */
FunctionIterator newFunctionIterator(int (*initFront)(void *),void * (*next)(void *,int*),int (*initBack)(void *),void * (*prev)(void*,int*));
int deleteFunctionIterator(FunctionIterator fi);

/* Iterator */
Iterator newIterator(void * object,IT_BOOL front);
void * nextIterator(Iterator i,int * error);
void * prevIterator(Iterator i,int * error);
void * getIterator(Iterator i,int * error);
int deleteIterator(Iterator i);

#endif
