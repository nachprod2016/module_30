#pragma once

#include <vector>

class ThreadQuickSort
{
public:
    std::vector<int> & vector;
    int left, right;
public:
    ThreadQuickSort(std::vector<int> &, int, int);
    ~ThreadQuickSort() = default;
    bool sort(int &, int &);
    std::vector<int> & getData(int &, int &);
};