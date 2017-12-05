#include "Vector.h"

#include <Iterator.h>

const Container Vector = {NULL,newVector,setFreeCallBackVector,deleteVector,pushBackVector,pushFrontVector,popBackVector,popFrontVector,lenVector,getVector,setVector};

#define VEC_DEFAULT_SIZE 128

struct _Vector_{
    FunctionIterator fi;
    void **tab;
    unsigned long space;
    unsigned long size;
    unsigned long begin;
    unsigned long current; 
    void (*free)(void *);
};
    
vector_t newVector(){
  struct _Vector_ * v = malloc(sizeof(*v));
	
  if(v){
    v->tab = malloc(VEC_DEFAULT_SIZE*sizeof(*(v->tab)));
    if(v->tab){
      v->fi=newFunctionIterator(initIteratorFrontVector,nextIteratorVector,initIteratorBackVector,prevIteratorVector);
      if(v->fi){
	v->begin=0;
	v->size=0;
	v->space=VEC_DEFAULT_SIZE;
	v->current=VEC_DEFAULT_SIZE;
	v->free=NULL;
      }else{
	free(v->tab);
	free(v);
	v=NULL;
      }
    }else{
      free(v);
      v=NULL;
    }
  }
  
  return (vector_t)v;
}

int setFreeCallBackVector(vector_t v,void (*yourFree)(void *)){
  int error = 1;
	
  if(v){
    ((struct _Vector_*)v)->free=yourFree;
    error=0;
  }
	
  return error;
}

void deleteVector(vector_t v){
  unsigned long     i;
  struct _Vector_ * vec	  = v;
	
  if(v){
    if(vec->tab){
      if(vec->free){
	for(i = vec->begin; i < vec->begin + vec->size; ++i){
	  vec->free(vec->tab[i]);
	}
      }
      free(vec->tab);
      deleteFunctionIterator(vec->fi);
    }
    free(v);
  }
}

int pushBackVector(vector_t v, void * value){
  struct _Vector_  * vec   = v;
  void            ** tmp;
  int                error = 1;
  unsigned long      i;
	
  if(v){
    if(vec->size >= vec->space){
      tmp=malloc((vec->space<<1)*sizeof(*tmp));
      if(tmp){
	vec->space<<=1;
	error=0;
	for(i=0; i<vec->size; ++i){
	  tmp[i]=vec->tab[i];
	}
	free(vec->tab);
	vec->tab=tmp;
	vec->tab[vec->size]=value;
	++vec->size;
      }
    }else{
      error=0;
      if(vec->begin && vec->begin+vec->size>=vec->space){
	for(i = 0; i<vec->size; ++i){
	  vec->tab[i]=vec->tab[i+vec->begin];
	}
	vec->begin=0;
      }		
      vec->tab[vec->begin+vec->size]=value;
      ++vec->size;
    }
  }
	
  return error;
}

int pushFrontVector(vector_t v, void* value){
  struct _Vector_  * vec   = v;
  void            ** tmp;
  unsigned long      i;
  int                error = 0;
	
  if(v){
    if(vec->size>=vec->space){
      tmp=malloc((vec->space<<1)*sizeof(*tmp));
      if(tmp){
	vec->space<<=1;
	for(i=0;i<vec->size;++i){
	  tmp[i+1]=vec->tab[i];
	}
	tmp[0]=value;
	free(vec->tab);
	vec->tab=tmp;
	++vec->size;
	error=0;
      }
    }else{
      error=0;
      if(vec->begin){
	--vec->begin;
	++vec->size;
	vec->tab[vec->begin]=value;
      }else{
	for(i=vec->size; i; --i){
	  vec->tab[i]=vec->tab[i-1];
	}
	vec->tab[0]=value;
	++vec->size;
      }
    }
  }
	
  return error;
}

void * popBackVector(vector_t v){
  struct _Vector_ * vec = v;
  void            * res = NULL;
  
  --vec->size;
  res=vec->tab[vec->begin+vec->size];
	
  return res;
}

void * popFrontVector(vector_t v){
  struct _Vector_ * vec = v;
  void            * res = NULL;
  
  res=vec->tab[vec->begin];
  ++vec->begin;
  --vec->size;
	
  return res;
}

int initIteratorFrontVector(vector_t v){
  struct _Vector_ * vec   = v;
  int               error = 1;
	
  if(v && vec->size){
    vec->current = vec->begin;
    error = 0;
  }
	
  return error;
}

void * nextIteratorVector(vector_t v,int * error){
  struct _Vector_ * vec = v;
  void            * res = NULL;
  int               err = 1;
	
  if(v && vec->current>=vec->begin && vec->current<vec->begin+vec->size){
    err = 0;
    res = vec->tab[vec->current];
    ++vec->current;
  }else if(!v)
    err=-1;
  if(error)
    *error=err;

  return res;
}

int initIteratorBackVector(vector_t v){
  struct _Vector_ * vec   = v;
  int               error = 1;
	
  if(v && vec->size){
    vec->current = vec->begin+vec->size-1;
    error = 0;
  }
	
  return error;
}

void * prevIteratorVector(vector_t v,int * error){
  struct _Vector_ * vec = v;
  void            * res = NULL;
  int               err = 1;
	
  if(v && vec->current>=vec->begin && vec->current<vec->begin+vec->size){
    err = 0;
    res = vec->tab[vec->current];
    --vec->current;
  }else if(!v)
    err=-1;
  if(error)
    *error=err;

  return res;
}
 
unsigned long lenVector(vector_t v){
  unsigned long res = 0;

  if(v){
    res=((struct _Vector_ *)v)->size;
  }

  return res;
}

void * getVector(vector_t v,unsigned long id){
  void            * res = NULL;
  struct _Vector_ * vec = v;
  
  res=vec->tab[vec->begin+id];
	
  return res;
}

void * setVector(vector_t v,unsigned long id,void * value){
  struct _Vector_ * vec = v;
  void            * old = NULL;
        
  old = vec->tab[vec->begin+id];
  vec->tab[vec->begin+id]=value;
	
  return old;
}
