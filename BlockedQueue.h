#pragma once

#include "ThreadQuickSort.h"
#include <mutex>
#include <queue>
#include <condition_variable>

class BlockedQueue 
{
private:
    std::mutex m_locker;
    std::queue<ThreadQuickSort *> m_task_queue;
    std::condition_variable m_notifier;
public:
    BlockedQueue() = default;
    ~BlockedQueue() = default;
    void push(ThreadQuickSort *);
    void pop(ThreadQuickSort *(&));
    bool fast_pop(ThreadQuickSort *(&));
};