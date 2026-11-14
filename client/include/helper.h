#ifndef __HELPER_H__
#define __HELPER_H__
#include<stdbool.h>

bool verify_fd(int fd, char* process);

int mod (int val, int n);
int wrap(int value, int  max, int min);
#endif // __HELPER_H__