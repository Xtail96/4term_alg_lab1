#include "natural_merge_sort.h"
#include <iostream>

void mergeSortIterative(int *arr, int *buf, int size, bool output)
{
    /*
    // разбиение для простого слияния
    // размер блоков для сортировки: 1, 2, 4, 8, 16, ...
    for (int subsize = 1; subsize < size; subsize *= 2)
    {
        // выводим массив на очередном этапе сортировки
        if (output)
        {
            for (int i = 0; i < size; i += 1)
            {
                std::cout << arr[i] << ' ';
                if ((i + 1) % subsize == 0)
                    std::cout << "| ";
                else
                    std::cout << "  ";
            }
            std::cout << '\n';
        }

        // для каждой пары блоков
        // сливаем два соседних блока
        for (int left = 0; left < size - 1; left += 2 * subsize)
        {
            int middle = std::min(left + subsize - 1, size - 1);
            int right = std::min(left + 2 * subsize - 1, size - 1);
            merge(arr, buf, left, middle, right);
        }
    }
    */
    // разбиение для естественного слияния
    std::vector< std::pair<int, int> > edges;
    edges.reserve(size);
    int leftEdge = 0;
    for(int i = 1; i < size; i++)
    {
        if(arr[i-1]>arr[i])
        {
            edges.push_back(std::make_pair(leftEdge, i-1));
            leftEdge = i;
        }
    }
    edges.push_back(std::make_pair(leftEdge, size-1));

    for(int subSize = 1; subSize < edges.size(); subSize*=2)
    {



        for(int leftEdge = 0; leftEdge < edges.size(); leftEdge+=2*subSize)
        {

            int middleEdge= std::min(leftEdge + subSize - 1, (int)edges.size() - 1);
            int rightEdge = std::min(leftEdge + 2 * subSize - 1, (int)edges.size() - 1);

            int left = edges[leftEdge].first;
            int middle = edges[middleEdge].second;
            int right = edges[rightEdge].second;

            if(output)
            {
                std::cout<<"["<<left<<" "<<middle<<"] ["<<middle+1<<" "<<right<<"]"<<std::endl;
                std::cout<<"Array1: ";
                printArray(arr, left, middle);
                std::cout<<std::endl;
                std::cout<<"Array2: ";
                printArray(arr, middle+1, right);
                std::cout<<std::endl;
            }


            merge(arr, buf, left, middle, right);
            if(output)
            {
                std::cout<<"Result: ";
                printArray(arr, left, right);
                std::cout<<std::endl;
            }


            merge(arr, buf, left, middle, right);

            if(output)
            {
                std::cout<<"Origin: ";
                printArray(arr, 0, size-1);
                std::cout<<std::endl<<std::endl;
            }

        }
    }

}


void merge(int *arr, int *buf, int left, int middle, int right)
{
    // текущая позиция чтения из левой части массива
    int l = left;
    // текущая позиция чтения из правой части массива
    int r = middle + 1;
    // текущая позиция записи в буфер
    int b = 0;

    // слияние, пока есть хотя бы 1 элемент в каждой части массива
    while ((l <= middle) && (r <= right))
    {
        // записываем в буфер меньший элемент из левой и правой частей
        if (arr[l] < arr[r])
            buf[b++] = arr[l++];
        else
            buf[b++] = arr[r++];
    }

    // одна из частей массива закончилась
    // копируем остаток другой части в конец буфера
    while (l <= middle) // левая часть
        buf[b++] = arr[l++];
    while (r <= right) // правая часть
        buf[b++] = arr[r++];

    // копируем буфер в исходный массив
    for (int i = 0; i <= right - left; i++)
        arr[left + i] = buf[i];
}


void printArray(int *arr, int begin, int end)
{
    for (int i = begin; i < end; i++)
        std::cout << arr[i] << ' ';
    std::cout << arr[end];
}
