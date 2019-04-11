#include <iostream>
#include <unistd.h>

int main() {
    for (int i = 0; i < 100500; ++i) {
        std::cerr << 'X';
        usleep(1E5);
    }
}
