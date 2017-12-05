#include "Iterator.h"

struct _Iterator_{
  void * object;
  void * current;
  int currError;
  IT_BOOL front;
};

struct _FunctionIterator_{
  int (*initFront)(void*);
  void * (*next)(void*,int*);
  int (*initBack)(void*);
  void * (*prev)(void*,int*);
};

/* FunctionIterator */
FunctionIterator newFunctionIterator(int (*initFront)(void *),void * (*next)(void *,int*),int (*initBack)(void *),void * (*prev)(void*,int*)){
  struct _FunctionIterator_ * fi = NULL;
	
  if((initFront && next) || (initBack && prev)){
    fi = malloc(sizeof(*fi));
    if(fi){
      if(initBack && prev){
	fi->prev=prev;
	fi->initBack=initBack;
      }else{
	fi->prev=NULL;
	fi->initBack=NULL;
      }
      if(initFront && next){
	fi->initFront=initFront;
	fi->next=next;
      }else{
	fi->next=NULL;
	fi->initFront=NULL;
      }
    }
  }
	
  return fi;
}

int deleteFunctionIterator(FunctionIterator fi){
  int error = 1;

  if(fi){
    free(fi);
    error = 0;
  }

  return error;
}

/* Iterator */
Iterator newIterator(void * object,IT_BOOL front){
  struct _Iterator_ 	    * i     = NULL;
  struct _FunctionIterator_ * fi;
  int                         error = 0;
	
  if(object){
    fi = *(struct _FunctionIterator_ **)object;
    if((front && fi->initFront && fi->next) || (!front && fi->initBack && fi->prev)){
      i = malloc(sizeof(*i));
      if(i){
	switch(front){
	case IT_TRUE:
	  error=fi->initFront(object);
	  if(!error){
	    i->current=fi->next(object,&(i->currError));
	  }
	  break;
	case IT_FALSE:
	  error=fi->initBack(object);
	  if(!error){
	    i->current=fi->prev(object,&(i->currError));
	  }
	  break;
	}
	i->front=front;
	i->object=object;
	if(error){
	  free(i);
	  i=NULL;
	}
      }
    }
  }
	
  return (void *)i;
}

void * nextIterator(Iterator i,int * error){
  struct _Iterator_         * it  = i;
  void		            * res = NULL;
  struct _FunctionIterator_ * fi;
  int                         err = -1;
	
  if(i){
    fi=*(struct _FunctionIterator_ **)(it->object);
    if(fi->next){
      if(!it->front){
	fi->next(it->object,NULL);
	fi->next(it->object,&(it->currError));
	it->front=IT_TRUE;
      }
      res = it->current;
      err = it->currError;
      it->current = fi->next(it->object,&(it->currError));
    }
  }
  if(error)
    *error=err;
	
  return res;
}

void * prevIterator(Iterator i,int * error){
  struct _Iterator_         * it  = i;
  void		            * res = NULL;
  struct _FunctionIterator_ * fi;
  int                         err = -1;
	
  if(i){
    fi=*(struct _FunctionIterator_ **)(it->object);
    if(fi->prev){
      if(it->front){
	fi->prev(it->object,NULL);
	fi->prev(it->object,&(it->currError));
	it->front=IT_FALSE;
      }
      res = it->current;
      err = it->currError;
      it->current = fi->prev(it->object,&(it->currError));
    }
  }
  if(error)
    *error=err;
	
  return res;
}

void * getIterator(Iterator i,int * error){
  void * res = NULL;
  int    err = -1;
	
  if(i){
    res=((struct _Iterator_ *)i)->current;
    err=((struct _Iterator_ *)i)->currError;
  }
  if(error)
    *error=err;
	
  return res;
}

int deleteIterator(Iterator i){
  int error = 1;
	
  if(i){
    error = 0;
    free(i);
  }
	
  return error;
}
