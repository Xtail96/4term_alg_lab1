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
    int leftFirst = -1;
    int rightFirst = -1;
    int rightSecond = -1;


    while(rightFirst != size-1 && rightSecond != size-1)
    {
        leftFirst = 0;
        //rightFirst = -1;
        //rightSecond = -1;
        for(int i = 0; i < size-1; i++)
        {
            if(rightFirst != -1 && rightSecond != -1)
            {
                std::cout<<"Array1: ";
                printArray(arr, leftFirst, rightFirst);
                std::cout<<std::endl;
                std::cout<<"Array2: ";
                printArray(arr, rightFirst+1, rightSecond);

                merge(arr, buf, leftFirst, rightFirst, rightSecond);

                std::cout<<std::endl;
                std::cout<<"Result: ";
                printArray(arr, leftFirst, rightSecond);
                std::cout<<std::endl;
                std::cout<<"Origin: ";
                printArray(arr, 0, size-1);
                std::cout<<std::endl;
                std::cout<<std::endl;


                leftFirst = rightSecond+1;
                rightFirst = -1;
                rightSecond = -1;
            }

            if(arr[i]>arr[i+1])
            {
                if(rightFirst == -1)
                {
                    rightFirst = i;
                    std::cout<<leftFirst<<" "<<rightFirst<<std::endl;
                }
                else
                {
                    rightSecond = i;
                    std::cout<<rightFirst+1<<" "<<rightSecond<<std::endl<<std::endl;
                }
            }
            else
            {

                if(i == size-2 && rightFirst != -1)
                {
                    rightSecond = i+1;
                    std::cout<<rightFirst+1<<" "<<rightSecond<<std::endl<<std::endl;
                }
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
