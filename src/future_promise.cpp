#include <iostream>
#include <thread>
#include <future>

void initiazer(std::promise<int> *promObj)
{
    std::cout << "Inside thread" << std::endl;
    promObj->set_value(35);
}

int main ()
{
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread my_thread(initiazer, &promiseObj);
    std::cout << "Trying to show the value from future obj" << std::endl;
    std::cout << futureObj.get() << std::endl;
    my_thread.join();
    return 0;
}