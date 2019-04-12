#include <signal.h>
#include <unistd.h>

static sig_atomic_t sigint_flag;

static void sigint_handler(int signo) {
    if (signo == SIGINT) {
        sigint_flag = 1;
        printf("SIGINT caught\n");
        raise(SIGUSR1);
        printf("SIGUSR1 sent\n");
    } else {
        assert(signo == SIGUSR1);
        printf("SIGUSR1 caught\n");
    }
}

int main() {
    signal(SIGINT, sig_handler);
    signal(SIGUSR1, sig_handler);

    for(;;) {
        if (sigint_flag) {
            printf("SIGINT caught\n");
            sigint_flag = 0;
        }
        sleep(1);
    }
}
