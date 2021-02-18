#include <iostream>
#include <thread>

class DisplayThread
{
public:
    void operator()()
    {
        for (int i = 0; i < 2; ++i)
        {
            std::cout << "Inside thread function from DisplayThread object..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

// Class able to use call a thread using Function Pointer, Function Object, and Lambda Function as constructor
class ThreadPart1
{
private:
    std::thread my_thread;
public:
    ThreadPart1()
    {
        std::cout << "Constructor..." << std::endl;
    }

    // Had to add the `static` to the function
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

    void construct_thread_function_object()
    {
        this->my_thread = std::thread(DisplayThread());
    }

    void join()
    {
        my_thread.join();
    }

    std::thread::id get_id()
    {
        return my_thread.get_id();
    }
};

int main()
{
    ThreadPart1 my_thread_exercise;
    my_thread_exercise.construct_thread_function_static();
    std::cout << "My current tread ID is: " << my_thread_exercise.get_id() << std::endl;
    my_thread_exercise.join();

    // Using Lambda
    std::cout << "Now using lambda..." << std::endl;
    my_thread_exercise.construct_thread_function_lambda();
    std::cout << "My current tread ID is: " << my_thread_exercise.get_id() << std::endl;
    my_thread_exercise.join();

    // Using Function Object
    std::cout << "Now using function object..." << std::endl;
    my_thread_exercise.construct_thread_function_object();
    std::cout << "My current tread ID is: " << my_thread_exercise.get_id() << std::endl;
    my_thread_exercise.join();

    return 0;
}