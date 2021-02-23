#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class Application
{
private:
    std::condition_variable cv;
    std::mutex my_mutex;
    bool data_loaded;
public:
    Application():data_loaded(false){}
    void LoadData()
    {
        std::cout << "Loading Data from XML... " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::lock_guard<std::mutex> guard(my_mutex);
        data_loaded = true;
        cv.notify_one();
    }
    bool isDataLoaded()
    {
        return data_loaded;
    }
    void ConnectToServer()
    {
        std::cout << "Do Some Handshaking... " << std::endl;
        
        std::unique_lock<std::mutex> unique_mlock(my_mutex);

        cv.wait(unique_mlock, std::bind(&Application::isDataLoaded, this));
        std::cout << "Do Some Processing With XML Data... " << std::endl;
    }
};

int main ()
{
    Application app;
    std::thread thread_main(&Application::ConnectToServer, &app);
    std::thread thread_load(&Application::LoadData, &app);

    if(thread_load.joinable())
    {
        thread_load.join();
    }
    if(thread_main.joinable())
    {
        thread_main.join();
    }

    return 0;
}