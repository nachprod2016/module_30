#include "ThreadPool.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <future>


int main()
{
    srand(time(NULL));
    std::string str;
    while (true)
    {
        std::cout << "1 - Сортировать случайный массив" << std::endl;
        std::cout << "0 - Завершить программу" << std::endl;
        std::cin >> str;
        if (str == "1")
        {
            ThreadPool p;
            std::vector<int> v;
            std::cout << "Размер массива: ";
            std::cin >> str;
            int size = atoi(&str[0]);
            if (size == 0)
            {
                continue;
            }
            std::cout << "Исходный массив: ";
            for (int i = 0; i < size; i++)
            {
                int a = rand() % 80 + 10;
                std::cout << a << " ";
                v.push_back(a);
            }
            std::cout << std::endl;
            p.push_task(new ThreadQuickSort(v, 0, size - 1));
            std::future<void> f = std::async(std::launch::async, [&p](){ p.start();});
            f.get();
            std::cout << "Отсортированный массив: ";
            for (int i = 0; i < size; i++)
            {
                std::cout << v[i] << " ";
            }
            std::cout << std::endl;
        }
        else if (str == "0")
        {
            break;
        }
    }
}