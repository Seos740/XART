#include "malloc.c"

#define uint32_t __CHAR32_TYPE__
#define uint64_t LONG

uint64_t syscall_handler(uint64_t syscall_num, uint64_t arg) {
    if (syscall_num == 0) {
        return arg + 1337;
    }
    return 0xFFFFFFFFFFFFFFFF;
}