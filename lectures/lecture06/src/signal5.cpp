#include <signal.h>
#include <unistd.h>

static unsigned counter = 0;

static void sigint_handler(int signo) {
    counter += 100500;
    printf("SIGINT caught\n");
}

static void non_reentrant_func() {
    for (;;) {
        const unsigned prev_counter = counter;
        ++counter;
        assert(prev_counter + 1 == counter);
    }
}

int main() {
    signal(SIGINT, sigint_handler);
    non_reentrant_func();
}
