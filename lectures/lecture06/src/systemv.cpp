#include <iostream>
#include <cstddef>
#include <cassert>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    const std::size_t size = 10 * 4096;
    const auto shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | IPC_EXCL);
    assert(shmid != -1);

    auto address = shmat(shmid, nullptr, 0);
    if (address == (void*) -1) {
        std::cerr << "Cannot attach shared memory: " << strerror(errno) << std::endl;
    }
    assert(address != (void*) -1);

    std::cout << "Shared memory attached at: " << address << std::endl;

    pause();
}
