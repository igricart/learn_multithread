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

// Create an example to illustrate a pointer to member
struct Foo {
    int value;
    void f() { std::cout << "f(" << this->value << ")\n"; }
    void g() { std::cout << "g(" << this->value << ")\n"; }
};

void apply(Foo* foo1, Foo* foo2, void (Foo::*fun)()) {
    (foo1->*fun)();  // call fun on the object foo1
    (foo2->*fun)();  // call fun on the object foo2
}

int main() {

    // SO example about bind calling member function and how to use pointer to member
    Foo foo1{1};
    Foo foo2{2};

    apply(&foo1, &foo2, &Foo::f);
    apply(&foo1, &foo2, &Foo::g);

    // Bind exercise
    BindExercise my_bind;
    my_bind.add_by_five_global(1);
    my_bind.add_by_three_member_function(1);
}