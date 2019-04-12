#include <iostream>
#include <unistd.h>

int main() {
    for (int i = 0; i < 100500; ++i) {
        std::cout << 'X' << sdt::endl;
        usleep(1E5);
    }
}
