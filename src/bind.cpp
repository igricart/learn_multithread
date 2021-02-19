#include <functional>
#include <iostream>

int add_global(int first, int second)
{
    return first + second;
}

class BindExercise
{
private:
public:
    BindExercise()
    {
        std::cout << "Let's get this rolling" << std::endl;
    }

    int add (int first, int second)
    {
        return first + second;
    }

    int add_by_five_global(int first)
    {
        std::function<int (int)> add_func = std::bind(&add_global, std::placeholders::_1, 5);
        int result = add_func(first);
        std::cout << "Result from add_by_five is... " << result << std::endl;
    }

    int add_by_five(int first)
    {
        //auto add_func = std::bind(&BindExercise::add, std::placeholders::_1, 5);
        //int result = add_func(first);
        //std::cout << "Result from add_by_five is... " << result << std::endl;
    }
};

int main()
{
    BindExercise my_bind;
    my_bind.add_by_five_global(1);
}