#include <iostream>
#include <thread>

class DisplayThread
{
public:
    void operator()()
    {
        for (int i = 0; i < 2; ++i)
        {
            std::cout << "Inside thread function" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

class ThreadPart1
{
private:
    std::thread my_thread;
public:
    thread_part1()
    {
        std::cout << "Constructor" << std::endl;
    }
    static void static_thread_function()
    {
        for (int i = 0; i < 2; ++i)
        {
            std::cout << "Inside thread function" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void thread_function()
    {
        for (int i = 0; i < 2; ++i)
        {
            std::cout << "Inside thread function" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void construct_thread_function_static()
    {
        this->my_thread = std::thread(this->static_thread_function);
    }

    void construct_thread_function_lambda()
    {
        this->my_thread = std::thread([](){
          for (int i = 0; i < 2; ++i)
            {
                std::cout << "Inside thread function" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }});
    }

    void join()
    {
        my_thread.join();
    }
};

int main()
{
    thread_part1 my_thread_exercise;
    my_thread_exercise.construct_thread_function_static();
    my_thread_exercise.join();
    return 0;
}