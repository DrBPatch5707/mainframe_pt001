#ifndef __DISPATCH_H__
#define __DISPATCH_H__

#include<display.h>


typedef struct DispatchArgs  {
    Display* dsp;
}DispatchArgs;


typedef int (*DispatchFunc)(DispatchArgs*);

typedef struct DispatchEntry DispatchEntry;

DispatchEntry* init_dispatch_hm();


int dispatch(Display*, DispatchArgs* args);

int defaultDispatch(DispatchArgs*);

int exitDispatch(DispatchArgs*);
#endif // __DISPATCH_H__