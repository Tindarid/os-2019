#include <signal.h>
#include <unistd.h>

static sig_atomic_t sigint_flag;

static void sigint_handler(int signo) {
    sigint_flag = 1;
}

int main() {
    signal(SIGINT, sigint_handler);

    for(;;) {
        if (sigint_flag) {
            printf("SIGINT caught\n");
            sigint_flag = 0;
        }
        sleep(1);
    }
}
