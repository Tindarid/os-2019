#include <signal.h>
#include <unistd.h>

static void sigint_handler(int signo) {
    printf("SIGINT caught\n");
}

int main() {
    signal(SIGINT, sigint_handler);

    for(;;) {
        sleep(10000);
        printf("hm\n");
    }
}
