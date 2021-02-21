#include <iostream>
#include <memory>
#include <thread>
#include <functional>

class ThreadWithArguments
{
private:
    std::thread my_thread;

public:
    ThreadWithArguments()
    {
        std::cout << "Class Constructor..." << std::endl;
    }

    void PassInt(int x)
    {
        my_thread = std::thread(std::bind(&ThreadWithArguments::ThreadCallbacSum5, this, x));
    }

    void ThreadCallbacVoid()
    {
        std::cout << "Inside Thread Callback and not returning anything" << std::endl;
    }

    void ThreadCallbacSum5(int x)
    {
        std::cout << "Inside Thread Callback and adding 5, giving the result..." << x + 5 << std::endl;
    }

    void ThreadJoin()
    {
        if (my_thread.joinable())
        {
            my_thread.join();
        }
    }

};

int main()
{
    ThreadWithArguments my_exercise;
    my_exercise.PassInt(3);
    my_exercise.ThreadJoin();
    return 0;
}