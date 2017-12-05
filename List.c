#include "List.h"

#include <Iterator.h>

const Container List = {NULL,newList,setFreeCallBackList,deleteList,pushBackList,pushFrontList,popBackList,popFrontList,lenList,getList,setList};

typedef struct _Element_{
  struct _Element_ * next;
  struct _Element_ * prev;
  void * data;
}_Element_;
struct _List_{
  FunctionIterator fi;
  _Element_ * first;
  _Element_ * last;
  _Element_ * current;
  unsigned long size;
  void (*free)(void *);
};

list_t newList(){
  struct _List_    * res = malloc(sizeof(*res));
  FunctionIterator   fi;
	
  if(res){
    fi=newFunctionIterator(initIteratorFrontList,nextIteratorList,initIteratorBackList,prevIteratorList);
    if(fi){
      res->fi=fi;
      res->first = NULL;
      res->last = NULL;
      res->size = 0;
      res->current = NULL;
      res->free=NULL;
    }else{
      free(res);
      res=NULL;
    }
  }
	
  return res;
}

void deleteList(list_t l){
  struct _List_ * lst   = l;
  _Element_     * e,
                * tmp;
	
  if(l){
    e = lst->first;
    while(e){
      tmp = e->next;
      if(lst->free){
	lst->free(e->data);
      }
      free(e);
      e=tmp;
    }
    deleteFunctionIterator(lst->fi);
    free(l);
  }
}

static void addFirstElemList(struct _List_ * l, _Element_ * e){
  l->first = e;
  l->last = e;
  l->size = 1;
  e->prev = NULL;
  e->next = NULL;
}

int pushBackList(list_t l, void * value){
  int             error = 1;
  struct _List_ * lst   = l;
  _Element_	* e;
	
  if(lst){
    e=malloc(sizeof(*e));
    if(e){
      e->data=value;
      if(lst->first){
	lst->last->next=e;
	e->prev=lst->last;
	e->next=NULL;
	lst->last=e;
	++lst->size;
      }else{
	addFirstElemList(lst,e);
      }
      error = 0;
    }else{
      error = 2;
    }
  }
	
  return error;
}

int pushFrontList(list_t l,void * value){
  int             error = 1;
  struct _List_ * lst	= l;
  _Element_     * e;
	
  if(lst){
    e=malloc(sizeof(*e));
    if(e){
      e->data=value;
      if(lst->first){
	lst->first->prev=e;
	e->next=lst->first;
	e->prev=NULL;
	lst->first=e;
	++lst->size;
      }else{
	addFirstElemList(lst,e);
      }
      error = 0;
    }else{
      error = 2;
    }
  }
	
  return error;
}

void * popBackList(list_t l){
  struct _List_ * lst   = l;
  void          * res   = NULL;
  _Element_     * poped;
	
  if(l && lst->last){
    res=lst->last->data;
    poped=lst->last;
    if(lst->current==poped){
      lst->current=NULL;
    }
    lst->last=poped->prev;
    --lst->size;
    if(!lst->size){
      lst->first=NULL;
    }else{
      lst->last->next=NULL;
    }
    free(poped);
  }
	
  return res;
}

void * popFrontList(list_t l){
  struct _List_ * lst   = l;
  void          * res   = NULL;
  _Element_     * poped;
	
  if(l && lst->first){
    res=lst->first->data;
    poped=lst->first;
    if(lst->current==poped){
      lst->current=poped->next;
    }
    lst->first=poped->next;
    --lst->size;
    if(!lst->size){
      lst->last=NULL;
    }else{
      lst->first->prev=NULL;
    }
    free(poped);
  }
  
  return res;
}

static _Element_ * searchInList(struct _List_ * lst, unsigned id){
  unsigned long   i;
  _Element_     * src;
	
  if(lst->size/2<id){
    i=lst->size-1;
    src=lst->last;
    while(i>id){
      --i;
      src=src->prev;
    }
  }else{
    i=0;
    src=lst->first;
    while(i<id){
      ++i;
      src=src->next;
    }
  }
	
  return src;
}

int pushList(list_t l,unsigned long id,void* value){
  struct _List_ * lst   = l;
  _Element_     * e     = malloc(sizeof(*e)),
                * src;
  int             error = 1;
	
  if(l && e){
    error=0;
    e->data=value;
    if(lst->size){
      src=searchInList(lst,id);
      if(lst->size/2<id){
	e->next=src->next;
	e->prev=src;
	if(src->next){
	  src->next->prev=e;
	}
	src->next=e;
      }else{
	e->next=src;
	e->prev=src->prev;
	if(src->prev){
	  src->prev->next=e;
	}
	src->prev=e;
      }
      ++lst->size;
    }else{
      addFirstElemList(lst,e);
    }
  }
	
  return error;
}

void * popList(list_t l,unsigned long id){
  struct _List_ * lst   = l;
  _Element_     * poped;
  void          * res   = NULL;
	
  if(l && lst->size>id){
    poped=searchInList(lst,id);
    if(lst->current==poped){
      lst->current=poped->next;
    }
    if(poped->next){
      poped->next->prev=poped->prev;
    }
    if(poped->prev){
      poped->prev->next=poped->next;
    }
    res=poped->data;
    free(poped);
    --lst->size;
  }
	
  return res;
}

void * setList(list_t l, unsigned long id, void * value){
  struct _List_ * lst = l;
  void          * old = NULL;
  _Element_     * src;
	
  if(l && lst->size>id && value){
    src=searchInList(lst,id);
    old=src->data;
    src->data=value;
  }
	
  return old;
}

void * getList(list_t l, unsigned long id){
  struct _List_ * lst = l;
  void          * res = NULL;
	
  if(l && lst->size>id){
    res=searchInList(lst,id)->data;
  }
	
  return res;
}

int initIteratorFrontList(list_t l){
  int error = 1;
	
  if(l){
    error=0;
    ((struct _List_ *)l)->current=((struct _List_ *)l)->first;
  }
	
  return error;
}

int initIteratorBackList(list_t l){
  int error = 1;
	
  if(l){
    error=0;
    ((struct _List_ *)l)->current=((struct _List_ *)l)->last;
  }
	
  return error;
}

void * nextIteratorList(list_t l,int * error){
  struct _List_ * lst = l;
  void          * res = NULL;
  int             err   = 1;
	
  if(l && lst->current){
    err=0;
    res=lst->current->data;
    lst->current=lst->current->next;
  }else if(!l)
    err = -1;
  if(error)
    *error=err;
	
  return res;
}

void * prevIteratorList(list_t l,int * error){
  struct _List_ * lst = l;
  void          * res = NULL;
  int             err   = 1;
	
  if(l && lst->current){
    err=0;
    res=lst->current->data;
    lst->current=lst->current->prev;
  }else if(!l)
    err = -1;
  if(error)
    *error=err;
	
  return res;
}

unsigned long lenList(list_t l){
  unsigned long res = 0;
	
  if(l){
    res=((struct _List_*)l)->size;
  }
	
  return res;
}

int setFreeCallBackList(list_t l,void (*yourFree)(void*)){
  int error = 1;
	
  if(l){
    ((struct _List_ *)l)->free=yourFree;
    error=0;
  }
	
  return error;
}
