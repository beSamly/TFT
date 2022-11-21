#pragma once

#include <thread>
#include <functional>

/*------------------
        ThreadSystem
-------------------*/

class ThreadSystem
{
public:
    ThreadSystem();
    ~ThreadSystem();

    void Launch(function<void(void)> callback);
    void Join();

    static void InitTLS();
    static void DestroyTLS();

    static void DoGlobalQueueWork();
    static void DistributeReservedJobs();

private:
    Mutex _lock;
    vector<thread> _threads;
};
