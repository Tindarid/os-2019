#include <iostream>

int main() {
    for (int i = 0; i < 100500; ++i) {
        std::cout << 'X';
    }
    for (int i = 0; i < 100500; ++i) {
        std::cerr << 'Y';
    }
}
