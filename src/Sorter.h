#pragma once
#include<vector>
#include<thread>
#include<iostream>


class Sorter
{
public:

    enum class SOTRTYPE{NONE, BUBLE, COCTAIL, INSERTION};

    static bool beginSort(std::vector<int>& arr, const SOTRTYPE stype);

    static bool sortIsEnd();

    static const std::vector<size_t>& getIndexs();

    static void setIterDelay(const intmax_t delay_ms);

    static intmax_t getIterDelay();
    
    static int getLastSwapCount();

    static SOTRTYPE getCurrSortType();
    
private:

    static void bubleSort(std::vector<int>& arr);

    static void coctailSort(std::vector<int>& arr);

    static void insertionSort(std::vector<int>& arr);
    
    static std::chrono::milliseconds delay;
    static std::vector<size_t> indexs;
    static int swapsCount;
    static bool sort_end;
    static SOTRTYPE currSort;
};
