#include "Deque.h"

#include <Iterator.h>

const Container Deque = {NULL,newDeque,setFreeCallBackDeque,deleteDeque,pushBackDeque,pushFrontDeque,popBackDeque,popFrontDeque,lenDeque,getDeque,setDeque};

#define DEFAULT_ARRAY_SIZE 256

struct _Array_{
    void ** tab;
    struct _Array_ * next;
    struct _Array_ * prev;
    unsigned long space;
    unsigned long size;
    unsigned long begin;
};
struct _Deque_{
    FunctionIterator fi;
    struct _Array_ * first;
    struct _Array_ * last;
    struct _Array_ * current;
    unsigned long currId;
    unsigned long size;
    void (*free)(void*);
};

static void newArray(struct _Array_ ** a){
    struct _Array_ * tmp = *a;
	
    *a = malloc(sizeof(**a));
    if(*a){
        (*a)->tab=malloc(DEFAULT_ARRAY_SIZE *sizeof(*((*a)->tab)));
        if((*a)->tab){
            (*a)->next=tmp;
            (*a)->space=DEFAULT_ARRAY_SIZE;
            (*a)->size=0;
            (*a)->prev=NULL;
            (*a)->begin=0;
        }else{
            free(*a);
            *a=NULL;
        }
    }
}
 
deque_t newDeque(){
    struct _Deque_ * d = malloc(sizeof(*d));
	
    if(d){
        d->fi=newFunctionIterator(initIteratorFrontDeque,nextIteratorDeque,initIteratorBackDeque,prevIteratorDeque);
        if(d->fi){
            d->first=NULL;
            newArray(&(d->first));
            if(d->first){
                d->current=NULL;
                d->last=d->first;
                d->size=0;
                d->free=NULL;
            }else{
                deleteFunctionIterator(d->fi);
                free(d);
                d=NULL;
            }
        }else{
            free(d);
            d=NULL;
        }
    }
	
    return d;
}

void deleteDeque(deque_t l){
    struct _Deque_ * d = l;
    struct _Array_ * a,
                   * tmp;
    unsigned long    i;
	
    if(d){
        a=d->first;
        while(a){
            if(d->free){
                for(i=a->begin;i<a->begin+a->size;++i){
                    d->free(a->tab[i]);
                }
            }
            free(a->tab);
            tmp=a->next;
            free(a);
            a=tmp;
        }
	deleteFunctionIterator(d->fi);
        free(d);
    }
}

int pushBackDeque(deque_t l, void * value){
    struct _Deque_ * d     = l;
    int              error = 1;
	
    if(d){
        if(d->last->begin+d->last->size>=d->last->space){
            newArray(&(d->last->next));
            if(!d->last->next){
                d=NULL;
            }else{
                d->last->next->prev=d->last;
                d->last=d->last->next;
            }
        }
        if(d){
            d->last->tab[d->last->begin+d->last->size]=value;
            ++d->last->size;
            ++d->size;
            error = 0;
        }
    }
	
    return error;
}

int pushFrontDeque(deque_t l,void * value){
    struct _Deque_ * d     = l;
    int              error = 1;
	
    if(l){
        if(!d->first->begin){
            newArray(&(d->first->prev));
            if(d->first->prev){
                d->first->prev->next=d->first;
                d->first=d->first->prev;
                d->first->begin=d->first->space;
            }else{
                d=NULL;
            }
        }
        if(d){
            error=0;
            d->first->tab[d->first->begin-1]=value;
            --d->first->begin;
            ++d->first->size;
            ++d->size;
        }
    }
	
    return error;
}

void * popBackDeque(deque_t l){
    struct _Deque_ * d   = l;
    void           * res = NULL;
    struct _Array_ * tmp;
	
    if(d && (d->last!=d->first || d->last->size)){
        res=d->last->tab[d->last->size+d->last->begin-1];
        --d->size;
        --d->last->size;
        if(!d->last->size && d->last!=d->first){
            tmp=d->last->prev;
            free(d->last->tab);
            free(d->last);
            tmp->next=NULL;
            d->last=tmp;
        }
    }
	
    return res;
}

void * popFrontDeque(deque_t l){
    struct _Deque_ * d   = l;
    struct _Array_ * tmp;
    void           * res = NULL;
	
    if(d && (d->last!=d->first || d->first->size)){
        res=d->first->tab[d->first->begin];
        --d->size;
        --d->first->size;
        ++d->first->begin;
        if(!d->first->size && d->last!=d->first){
            tmp=d->first->next;
            free(d->first->tab);
            free(d->first);
            tmp->prev=NULL;
            d->first=tmp;
        }
    }
	
    return res;
}

void * setDeque(deque_t l, unsigned long id, void * value){
    struct _Deque_ * d   = l;
    struct _Array_ * a;
    void           * old = NULL;
    unsigned long	   count = 0;

    if(d && id<d->size){
        a=d->first;
        while(count+a->size<=id){
            count+=a->size;
            a=a->next;
        }
        id-=count;
        old=a->tab[a->begin+id];
        a->tab[a->begin+id]=value;
    }

    return old;
}

void * getDeque(deque_t l, unsigned long id){
    struct _Deque_ * d   = l;
    struct _Array_ * a;
    void           * old = NULL;
    unsigned long    count = 0;

    if(d && id<d->size){
        a=d->first;
        while(count+a->size<=id){
            count+=a->size;
            a=a->next;
        }
        id-=count;
        old=a->tab[a->begin+id];
    }

    return old;
}

int initIteratorFrontDeque(deque_t l){
    struct _Deque_ * d = l;
    int              error = 1;
	
    if(d){
        d->current=d->first;
        d->currId=d->first->begin;
        error = 0;
    }
	
    return error;
}

int initIteratorBackDeque(deque_t l){
    struct _Deque_ * d     = l;
    int              error = 1;
	
    if(d){
        d->current=d->last;
        d->currId=d->last->begin+d->last->size-1;
        error = 0;
    }
	
    return error;
}

void * nextIteratorDeque(deque_t l,int * error){
    struct _Deque_ * d   = l;
    void           * res = NULL;
    int              err = 1;
	
    if(d && d->current){
        err = 0;
        res=d->current->tab[d->currId++];
        if(d->currId>=d->current->size+d->current->begin){
            d->current=d->current->next;
            if(d->current){
                d->currId=d->current->begin;
            }
        }
    }else if(!d)
        err = -1;
    if(error)
        *error=err;
	
    return res;
}

void * prevIteratorDeque(deque_t l,int * error){
    struct _Deque_ * d   = l;
    void           * res = NULL;
    int              err = 1;
	
    if(d && d->current){
        err = 0;
        res=d->current->tab[d->currId];
        if(d->currId==d->current->begin){
            d->current=d->current->prev;
            if(d->current){
                d->currId=d->current->begin+d->current->size-1;
            }
        }else{
            --d->currId;
        }
    }else if(!d)
        err = -1;
    if(error)
        *error=err;
	
    return res;
}

void * getCurrentDeque(deque_t l,int * error){
    struct _Deque_ * d = l;
    void           * res = NULL;
    int              err = 1;
	
    if(d && d->current){
        err = 0;
        res=d->current->tab[d->currId];
    }else if(!d)
        err = -1;
    if(error)
        *error=err;
	
    return res;
}

unsigned long lenDeque(deque_t l){
    unsigned long len = 0;
	
    if(l){
        len=((struct _Deque_ *)l)->size;
    }
	
    return len;
}

int setFreeCallBackDeque(deque_t l,void (*yourFree)(void *)){
    struct _Deque_ * d     = l;
    int              error = 1;
	
    if(d){
        error = 0;
        d->free=yourFree;
    }
	
    return error;
}
