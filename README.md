# prodcons

Producer–Consumer example in C++ using threads, semaphores, and atomic flag.

## Approaches Used

- **semaphores** (`sem_t`)
- **Atomic flag** (`std::atomic<bool>`)
- **C++11 threads** (`std::thread`)
- **<random>** for PRNG
- **Makefile** with GCC/G++

## Requirements

- GCC/G++ ≥ 5

## Build & Run

```bash
make
./prodcons
```
