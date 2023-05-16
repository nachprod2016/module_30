#pragma once

#include <mutex>

class Flag
{
private:
    bool flag;
    std::mutex m_locker;
public:
    Flag();
    ~Flag() = default;
    void setFlag();
    bool getFlag();
};