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
        // OBS 1
        // auto add_func = (add_global, std::placeholders::_1, 5); would also work because when a function is passed anywhere it decays into a pointer
        std::function<int (int)> add_func = std::bind(&add_global, std::placeholders::_1, 5);
        int result = add_func(first);
        std::cout << "Result from add_by_five is... " << result << std::endl;
    }

    int add_by_three_member_function(int first)
    {
        auto add_func = std::bind(&BindExercise::add, this, std::placeholders::_1, 3);
        int result = add_func(first);
        std::cout << "Result from add_by_three_member_function is... " << result << std::endl;
    }
};

int main()
{
    BindExercise my_bind;
    my_bind.add_by_five_global(1);
    my_bind.add_by_three_member_function(1);
}