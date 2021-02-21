#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex mu;
std::condition_variable cv;
bool finished = false;

void threadFunc()
{
    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::unique_lock<std::mutex> lock(mu);
        std:: cout << "Thread:  " << (0 - i) << "\n";
    }

    std::unique_lock<std::mutex> lock(mu);
    finished = true;
    cv.notify_one();
}

int main()
{
    {
        std::thread t1(threadFunc);
        t1.detach(); // Call `detach` to prevent blocking this thread

    } // Need to call `join` or `detach` before `thread` goes out of scope

    for (int i = 0; i < 5; ++i)
    {
        std::unique_lock<std::mutex> lock(mu);
        std::cout << "Main:  " << i << "\n";
    }

    std::cout << "End of Main\n";

    std::unique_lock<std::mutex> lock(mu);
    cv.wait(lock, [&finished]() { return finished; });

    return 0;
}