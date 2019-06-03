#include <assert.h>
#include <pthread.h>

static void* loop(void * arg) { }

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, loop, NULL);
    pthread_join(thread);
}
