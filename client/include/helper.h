#ifndef __HELPER_H__
#define __HELPER_H__
#include<stdbool.h>
#include <stddef.h>

bool verify_fd(int fd, char* process);

int mod (int val, int n);
int wrap(int value, int  max, int min);
void center(int* outX, int* outY, int pw, int ph, int cw, int ch);
size_t remove_char(char* txt, size_t size, char ch);
#endif // __HELPER_H__