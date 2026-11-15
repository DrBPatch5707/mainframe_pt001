#include<helper.h>
#include<stdbool.h>
#include <unistd.h>
#include<errno.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


//error message may be truncated if process string is to long
bool verify_fd(int fd, char* process) {
if (fd < 0) {
    const size_t SIZE = 90;
        char buf[SIZE] = {0};
        int s = snprintf(buf, SIZE, "%s errno: %d\n", process, errno);
        write(STDERR_FILENO, buf, s);
        return false;
    }
    return true;
}

int mod (int val, int n) {
    return val - n * floor((double)val / (double)n);
}

int wrap(int value, int  max, int min) {
    int n = max - min;
    if(n == 0) return min;
    return  (mod(mod((value - min), (n * 2)), n) + min);
}


void center(int* outX, int* outY, int pw, int ph, int cw, int ch) {
    if(outY == NULL || outX == NULL) return;
    *outX = (pw - cw) / 2; *outY = (ph - ch) / 2;
}


size_t remove_char(char* txt, size_t size, char ch) {
    size_t write = 0;
    for (size_t read = 0; read < size; read++) if(txt[read] != ch) txt[write++] = txt[read];
    for (size_t i = write; i < size; i++) txt[i] = '\0';
    return write;
}