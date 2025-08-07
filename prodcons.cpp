#include <iostream>
#include <random>
#include <thread>
#include <queue>
#include <semaphore.h>
#include <atomic>

constexpr int PRODUCE_COUNT = 100;

sem_t semFull;     // семафор готових елементів
sem_t semBinary;   // бінарний семафор (заміна mutex)
std::queue<int> buffer;
std::atomic<bool> done{false};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, 99); // гпсч

void producer() {
    for (int i = 0; i < PRODUCE_COUNT; ++i) {
        int number = dist(gen);

        sem_wait(&semBinary);
        buffer.push(number);
        sem_post(&semBinary);

        // сигналізуємо, що елемент додано
        sem_post(&semFull);
    }


    done = true; //кінець генерації чисел
    sem_post(&semFull); // будимо consumers
    sem_post(&semFull);
}

void consumer(int id) {
    while (true) {
        // чекаємо на додавання елементу
        sem_wait(&semFull);

        sem_wait(&semBinary);
        if (buffer.empty()) {
            sem_post(&semBinary);
            if (done) break;
            else continue;
        }
        int y = buffer.front();
        buffer.pop();
        sem_post(&semBinary);

        // семафор щоб коректно вдображались рядки, можна обійтись і без них
        sem_wait(&semBinary);
        std::cout << "Consumer " << id << " got: " << y << std::endl;
        sem_post(&semBinary);
    }
}

int main() {
    sem_init(&semFull,   0, 0);
    sem_init(&semBinary, 0, 1);

    std::thread prod(producer);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();

    sem_destroy(&semFull);
    sem_destroy(&semBinary);
    return 0;
}
