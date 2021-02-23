#include <iostream>
#include <thread>
#include <mutex>

class Application
{
private:
    std::mutex my_mutex;
    bool data_loaded;
public:
    Application():data_loaded(false){}
    void LoadData()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Loading Data from XML... " << std::endl;
        std::lock_guard<std::mutex> guard(my_mutex);
        data_loaded = true;
    }
    void ConnectToServer()
    {
        std::cout << "Do Some Handshaking... " << std::endl;
        my_mutex.lock();
        // Create a loop to wait for variable to be set, and after that runs a processing
        while(!data_loaded)
        {
            my_mutex.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            my_mutex.lock();
        }
        my_mutex.unlock();
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