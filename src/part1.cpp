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
class ThreadTutorial
{
private:
    std::thread my_thread;
public:
    ThreadTutorial()
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

    void detach()
    {
        my_thread.detach();
    }

    std::thread::id get_id()
    {
        return my_thread.get_id();
    }

    void exercise_thread_function_pointer()
    {
        std::cout << "Construct function pointer exercise..." << std::endl;
        this->construct_thread_function_static();
        std::cout << "My current tread ID is: " << this->get_id() << std::endl;
        if(this->my_thread.joinable()){this->detach();}
    }

    void exercise_thread_function_lambda()
    {
        std::cout << "Construct function lambda exercise..." << std::endl;
        this->construct_thread_function_static();
        std::cout << "My current tread ID is: " << this->get_id() << std::endl;
        if(this->my_thread.joinable()){this->detach();}
    }

    void exercise_thread_function_object()
    {
        std::cout << "Construct function object exercise..." << std::endl;
        this->construct_thread_function_object();
        std::cout << "My current tread ID is: " << this->get_id() << std::endl;
        if(this->my_thread.joinable()){this->detach();}
    }
};

int main()
{
    ThreadTutorial my_thread_exercise;
    my_thread_exercise.exercise_thread_function_pointer();

    // Using Lambda
    my_thread_exercise.exercise_thread_function_lambda();

    // Using Function Object
    my_thread_exercise.exercise_thread_function_object();

    // Time required to print information from detached threads, otherwise the main will be finished.
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}