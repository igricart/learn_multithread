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

    void ThreadCallbacVoid()
    {
        std::cout << "Inside Thread Callback and not returning anything" << std::endl;
    }

    // Callback using one argument and returning void
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

    void PassInt(int x)
    {
        my_thread = std::thread(std::bind(&ThreadWithArguments::ThreadCallbacSum5, this, x));
    }

    // Callback using two arguments and returning non-void
    // TODO: Still need to work on that to use and use the boolean value
    bool ThreadCallbackSum(int x, int y)
    {
        int sum = x + y;
        if(sum < 5)
        {
            std::cout << "Sum lower than 5, returning false" << std::endl;
            return false;
        } else
        {
            return true;
        }
    }

    // Callback caller
    // TODO: Use boolean returned by `ThreadCallbackSum`
    bool HigherThan5(int x, int y)
    {
        my_thread = std::thread(std::bind(&ThreadWithArguments::ThreadCallbackSum, this, x, y));
    }
};

// Test to pass argument by reference
void ThreadCallbackReference(int &x)
{
    int &y = x;
    ++y;
    std::cout << "Value of reference inside thread is..." << y << std::endl;
}

int main()
{
    ThreadWithArguments my_exercise;
    my_exercise.PassInt(3);
    my_exercise.ThreadJoin();

    my_exercise.HigherThan5(1,3);
    my_exercise.ThreadJoin();

    int x = 9;
    // Requies std::ref to pass x by reference to the callback
    std::thread my_ref_test(ThreadCallbackReference, std::ref(x));
    my_ref_test.join();
    std::cout << "Value of x is..." << x << std::endl;

    return 0;
}