#include "Flag.h"

Flag::Flag() : flag(false) {}

void Flag::setFlag()
{
    std::unique_lock<std::mutex> l(m_locker);
    if (flag == false)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }
}

bool Flag::getFlag()
{
    std::unique_lock<std::mutex> l(m_locker);
    return flag;
}