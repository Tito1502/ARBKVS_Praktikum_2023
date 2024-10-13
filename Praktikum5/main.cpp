#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Unsynchronized Threads
void threadFunction1() {
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c << " ";
    }
}

void threadFunction2() {
    for (int i = 0; i <= 32; ++i) {
        std::cout << i << " ";
    }
}

void threadFunction3() {
    for (char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c << " ";
    }
}

// Synchronized Threads with Mutex
std::mutex mtx;

void synchronizedThreadFunction1() {
    std::lock_guard<std::mutex> lock(mtx);
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c << " ";
    }
}

void synchronizedThreadFunction2() {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i <= 32; ++i) {
        std::cout << i << " ";
    }
}

void synchronizedThreadFunction3() {
    std::lock_guard<std::mutex> lock(mtx);
    for (char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c << " ";
    }
}

// Semaphore Class
class Semaphore {
public:
    explicit Semaphore(int count) : count(count) {}

    void wait(int id) {
        std::unique_lock<std::mutex> lock(mutex);
        if (count == 0)
        {
            std::cout << "\n--- Thread " << id << " wartet auf den Start: ---\n";
            condition.wait(lock);
            std::cout << "--- Thread " << id << " startet nun: ---\n";
        }
        --count;
    }

    void signal() {
        std::lock_guard<std::mutex> lock(mutex);
        ++count;
        std::cout << "\n--- Mutex freigegeben! Nächster Thread wird benachrichtigt. ---\n\n";
        condition.notify_one();
    }

private:
    std::mutex mutex;
    std::condition_variable condition;
    int count;
};

// Semaphore Threads
Semaphore sem1(1);

void semaphoreThreadFunction1() {
    sem1.wait(1);
    for (char c = 'a'; c <= 'z'; ++c) {     
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        std::cout << c << " ";
    }
    sem1.signal();
}

void semaphoreThreadFunction2() {
    sem1.wait(2);
    for (int i = 0; i <= 32; ++i) {  
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        std::cout << i << " ";        
    }
    sem1.signal();
}

void semaphoreThreadFunction3() {
    sem1.wait(3);
    for (char c = 'A'; c <= 'Z'; ++c) {  
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        std::cout << c << " ";        
    }
    sem1.signal();
}


void aufgabe1() {
    // Unsynchronized Threads
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    std::thread t3(threadFunction3);

    t1.join();
    t2.join();
    t3.join();
}

void aufgabe2() {
    // Synchronized Threads with Mutex
    std::thread t1_sync(synchronizedThreadFunction1);
    std::thread t2_sync(synchronizedThreadFunction2);
    std::thread t3_sync(synchronizedThreadFunction3);

    t1_sync.join();
    t2_sync.join();
    t3_sync.join();
}

void aufgabe3() {
    // Semaphore Threads
    std::thread t1_sem(semaphoreThreadFunction1);
    std::thread t2_sem(semaphoreThreadFunction2);
    std::thread t3_sem(semaphoreThreadFunction3);

    t1_sem.join();
    t2_sem.join();
    t3_sem.join();
}

int main() {
    //aufgabe1();
    //aufgabe2();
    aufgabe3();



    std::cout << "\n\n";
    return 0;
}
