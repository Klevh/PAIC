# PAIC

Package for All-Inside (generic) Containers in C.
  
This package gives three generic containers (double linked list, vector and deque) and a _generic_ generic container structure which allow you to create your own containers.
  
A generic iterator is also provided, and used in the three generic containers but not in the _generic_ generic container.

## What you will find in this read-me

* [Basic features](#basic-features)
* [Howto create your generic container](#how-to-create-your-generic-container)
* [How to use your generic container as a generic generic container](#how-to-use-your-generic-container-as-a-generic-generic-container)
* [How to use your generic container with generic iterators](#how-to-use-your-generic-container-with-generic-iterators)

## Basic features

There are six types that you can use in this package :
* vector_t : the generic vector
* list_t : the generic double linked list
* deque_t : the generic deque
* FunctionIterator : should be the first attribute of your self-made structure so that it can use provided generic iterators
* Iterator : the generic iterator
* Container : the _generic_ generic container

## How to create your generic container

Well ... For this part, it is your choice as of how you want to implement your container. What will be interesting are how use generic iterators with it and how can your container be used as a _generic_ generic container.
  
In the examples below, we will use this structure :
```c
struct static_array_50_t{
  int array[50];
};
typedef void * static_array_50_t; /* pointer to a struct static_array_50_t, void * is meant for generic generic container */
```
Of course this structure is neither useful nor a good practice, but it is simple enough to show how to use this package.

## How to use your generic container as a generic generic container

All you need to do for this to work, is to create a constant global variable of type Container with some predefine attributes. Let's explain it with an example.
```c
const Container StaticArray50 = {
    NULL, /* has to be NULL */
    new,
    setFreeCallback,
    delete,
    pushBack,
    pushFront,
    popBack,
    popFront,
    len,
    get,
    set
};
```
Those parameters are function pointers that define the behavior of your container.
Their descriptions and prototypes are :
* __new__ : `void * (void)` function to create an instance of your container
* __setFreeCallback__ : `int (void * container, void (*Free)(void *))` function to set the free callback (function to be called on each object of the container when it is freed)
* __delete__ : `void (void * container)` function to free the memory allocated to your container
* __pushBack__ : `int (void * container, void * element)` function to add an element to the back of the container
* __pushFront__ : `int (void * container, void * element)` function to add an element to the front of the container
* __popBack__ : `void * popBack(void * container)` function to remove and return the last element of the container
* __popFront__ : `void * popFront(void * container)` function to remove and return the first element of the container
* __len__ : `size_t (void * container)` function to return the number of elements in the container
* __get__ : `void * (void * container, size_t index)` function to get the (index + 1)th element of the container
* __set__ : `void * (void * container, size_t index, void * value)` function to set the (index + 1)th element of the container, return the old value of this element
They can be set to `NULL` if you do not want your container to have this behavior.
  
`int` return type replace `void` so that you can tell the user if the action failed or not.

## How to use your generic container with generic iterators

For now, this feature is quite unpractical so I will not explain how to use it. I am working on it.
