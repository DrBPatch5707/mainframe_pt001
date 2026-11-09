#include<helper.h>
#include<stdbool.h>
#include <unistd.h>
#include<errno.h>
#include<stdio.h>

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