#include <assert.h>
#include <dlfcn.h>

int main() {
    void* handle = dlopen("lib/x86_64-linux-gnu/libpthread.so.0", RTLD_LAZY);
    assert(handle);
    void* addr = disym(handle, "pthread_create");

    printf("Addr: %p\n", addr);

    dlclose(handle);
}
