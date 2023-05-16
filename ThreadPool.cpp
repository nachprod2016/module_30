#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(): m_thread_count(std::thread::hardware_concurrency()), m_thread_queues(m_thread_count), flags(m_thread_count) {}

void ThreadPool::start()
{
    for (int i = 0; i < m_thread_count; i++) 
    {
        m_threads.emplace_back(&ThreadPool::threadFunc, this, i);
    }
    for (int i = 0; i < m_thread_count; i++)
    {
        m_threads[i].join();
    }
}

void ThreadPool::threadFunc(int qindex) 
{
    while (true)
    {
        ThreadQuickSort * ob = nullptr;
        for (int i = 0; i < m_thread_count; i++) 
        {
            int a = (qindex + i) % m_thread_count;
            m_thread_queues[a].fast_pop(ob);
            if (ob != nullptr)
            {
                break;
            }
        }
        if (ob == nullptr)
        {
            setFlag(qindex);
            if (checkFlags() == true)
            {
                stop();
                return;
            }
            m_thread_queues[qindex].pop(ob);
            setFlag(qindex);
        }
        if (ob != nullptr)
        {
            int left_bound, right_bound, left, right;
            bool f = ob->sort(left_bound, right_bound);
            if (f == true)
            {
                std::vector<int> & vc = ob->getData(left, right);
                push_task(new ThreadQuickSort(vc, left, right_bound));
                push_task(new ThreadQuickSort(vc, left_bound, right));
            }
            delete ob;
        }
    }
}

void ThreadPool::stop() 
{
    for (int i = 0; i < m_thread_count; i++) 
    {
        ThreadQuickSort * ob = nullptr;
        m_thread_queues[i].push(ob);
    }
}

void ThreadPool::push_task(ThreadQuickSort * ob)
{
    int queue_to_push = m_index++ % m_thread_count;
    m_thread_queues[queue_to_push].push(ob);
}

bool ThreadPool::checkFlags()
{
   bool flag = true;
   for (int i = 0; i < flags.size(); i++)
   {
        if(flags[i].getFlag() == false)
        {
            flag = false;
            break;
        }
   }
   return flag;
}

void ThreadPool::setFlag(int i)
{
   flags[i].setFlag();
}