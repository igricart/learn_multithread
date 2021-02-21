#include <iostream>
#include <memory>
#include <thread>
#include <functional>

class ThreadWithArguments
{
private:
    std::thread my_thread;
    int ref_variable;
public:
    ThreadWithArguments()
    {
        std::cout << "Class Constructor... " << std::endl;
    }

    void ThreadCallbacVoid()
    {
        std::cout << "Inside Thread Callback and not returning anything" << std::endl;
    }

    // Callback using one argument and returning void
    void ThreadCallbacSum5(int x)
    {
        std::cout << "Inside Thread Callback and adding 5, giving the result... " << x + 5 << std::endl;
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

    void ThreadCallbackRef(int &x)
    {
        int &z = x;
        ++z;
        std::cout << "The new value of the variable passed by reference inside the new thread is... " << x << std::endl;
    }

    void PassIntRef(int &x)
    {
        std::cout << "The initial value of the variable is... " << x << std::endl;
        my_thread = std::thread(std::bind(&ThreadWithArguments::ThreadCallbackRef, this, std::ref(x)));
        my_thread.join();
        std::cout << "The value of the variable passed by reference after the thread is... " << x << std::endl;
    }
};

int main()
{
    ThreadWithArguments my_exercise;
    my_exercise.PassInt(3);
    my_exercise.ThreadJoin();

    my_exercise.HigherThan5(1,3);
    my_exercise.ThreadJoin();

    int x = 3;
    my_exercise.PassIntRef(x);
    return 0;
}