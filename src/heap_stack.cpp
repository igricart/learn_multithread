#include <iostream>
#include <memory>

int main()
{
    int value = 5;
    int* heap_value = new int;
    *heap_value = 10;
    std::shared_ptr<int> smart_int_ptr = std::make_shared<int>(5);

    std::cout << "I am testing heap and stack memories" << std::endl;
    
    delete heap_value;
    
    return 0;
}