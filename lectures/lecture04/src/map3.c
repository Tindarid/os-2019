#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main() {
    const size_t size = 4 * PAGE_SIZE;
    char *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(addr != MAP_FAILED);

    for (size_t i = 0; i < size; ++i) {
        addr[i] = 'X';
    }

    mprotect(&addr[3 * PAGE_SIZE], PAGE_SIZE, PROT_NONE);

    addr[3 * PAGE_SIZE - 1] = 'Y';
    addr[3 * PAGE_SIZE] = 'Y'; //Segmentation fault

    munmap(addr, size);
}
