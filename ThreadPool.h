#pragma once

#include <vector>
#include <thread>
#include "BlockedQueue.h"
#include "Flag.h"

class ThreadPool 
{
private:
    int m_thread_count;
    std::vector<std::thread> m_threads;
    std::vector<BlockedQueue> m_thread_queues;
    std::vector<Flag> flags;
    int m_index;
public:
    ThreadPool();
    ~ThreadPool() = default;
    void start();
    void stop();
    void push_task(ThreadQuickSort * ob);
    void threadFunc(int qindex);
    bool checkFlags();
    void setFlag(int i);
};