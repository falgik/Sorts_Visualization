#include "Sorter.h"

void Sorter::bubleSort(std::vector<int>& arr)
{
    sort_end = false;
    currSort = SOTRTYPE::BUBLE;
    indexs.resize(2, -1);
    swapsCount = 0;
    
    for (int j = arr.size() - 2; j >= 0; j--) {
        for (int i = 0; i <= j; i++) {

            auto tp = std::chrono::system_clock::now();

            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swapsCount++;
            }

            indexs[0] = i;
            indexs[1] = i + 1;

            std::this_thread::sleep_for(delay - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp));
        }
    }

    indexs[0] = -1;
    indexs[1] = -1;
    currSort = SOTRTYPE::NONE;
    sort_end = true;
}

void Sorter::coctailSort(std::vector<int>& arr)
{
    sort_end = false;
    currSort = SOTRTYPE::COCTAIL;

    indexs.resize(2, -1);
    swapsCount = 0;

    int l = 0;
    int r = arr.size() - 1;

    for (int j = 0; j < arr.size() / 2; j++) {
        for (int i = l; i < r; i++) {
            auto tp = std::chrono::system_clock::now();
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swapsCount++;
            }

            indexs[0] = i;
            indexs[1] = i + 1;
            std::this_thread::sleep_for(delay - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp));
        }

        r--;

        for (int i = r; i > l; i--) {
            auto tp = std::chrono::system_clock::now();
            if (arr[i] < arr[i - 1])
            {
                std::swap(arr[i], arr[i - 1]);
                swapsCount++;
            }

            indexs[0] = i;
            indexs[1] = i - 1;
            std::this_thread::sleep_for(delay - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp));
        }

        l++;
    }

    indexs[0] = -1;
    indexs[1] = -1;
    
    currSort = SOTRTYPE::NONE;
    sort_end = true;
}

void Sorter::insertionSort(std::vector<int>& arr)
{
    sort_end = false;
    currSort = SOTRTYPE::INSERTION;
    indexs.resize(3, -1);
    swapsCount = 0;


    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        indexs[2] = i;
        int j;

        for (j = i - 1; (j >= 0) && (arr[j] > key); j--)
        {
            auto tp = std::chrono::system_clock::now();

            arr[j + 1] = arr[j];

            swapsCount++;

            indexs[0] = j;
            indexs[1] = j + 1;

            std::this_thread::sleep_for(delay - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tp));
        }
       
        arr[j + 1] = key;
        indexs[2] = j+1;
        std::this_thread::sleep_for(delay);
    }

    indexs[0] = -1;
    indexs[1] = -1;
    indexs[2] = -1;
    currSort = SOTRTYPE::NONE;
    sort_end = true;
}

void Sorter::setIterDelay(const intmax_t delay_ms)
{
    delay = std::chrono::milliseconds(delay_ms);
}

intmax_t Sorter::getIterDelay()
{
    return delay.count();
}

int Sorter::getLastSwapCount()
{
    return swapsCount;
}

Sorter::SOTRTYPE Sorter::getCurrSortType()
{
    return currSort;
}

bool Sorter::beginSort(std::vector<int>& arr, const SOTRTYPE stype)
{
    if (!sort_end)
        return false;

    if (stype == SOTRTYPE::BUBLE){
        std::thread th([&arr]() {
            bubleSort(arr);
            });
        th.detach();
        return true;
    }
    else if (stype == SOTRTYPE::COCTAIL) {
        std::thread th([&arr]() {
            coctailSort(arr);
            });
        th.detach();
        return true;
    }
    else if (stype == SOTRTYPE::INSERTION) {
        std::thread th([&arr]() {
            insertionSort(arr);
            });
        th.detach();
        return true;
    }
 
    return false;
}

const std::vector<size_t>& Sorter::getIndexs()
{
    return indexs;
}

bool Sorter::sortIsEnd()
{
    return sort_end;
}

bool Sorter::sort_end = true; 
int Sorter::swapsCount = 0;
std::chrono::milliseconds Sorter::delay = std::chrono::milliseconds(5);
std::vector<size_t> Sorter::indexs = std::vector<size_t>(2, -1);
Sorter::SOTRTYPE Sorter::currSort = Sorter::SOTRTYPE::NONE;