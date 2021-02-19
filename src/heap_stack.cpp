#include <iostream>
#include <memory>
#include <vector>
#include <array>

/**
 * @brief Run something like `-exec x/64b 0x55555576ce70` or `x/16x` in `Debug Console` to see the memory
 * 
 * @return int 
 */

int main()
{
    int value = 5;
    int* heap_value = new int;
    *heap_value = 10;
    std::shared_ptr<int> smart_int_ptr = std::make_shared<int>(5);

    std::array<int, 5> my_heap_array = {1,2,3,4,5};

    std::cout << "I am testing heap and stack memories" << std::endl;
    
    delete heap_value;
    
    return 0;
}