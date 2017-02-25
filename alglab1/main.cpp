#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <chrono>

#include "natural_merge_sort.h"
//#include "timeresearch.h"

using namespace std;

// Ввод исходных данных, создание копии массива и ее сортировка
void inputData(int*& arr, int*& buf, int*& arr_sorted, int& N);


int main()
{
    // исследование времени работы алгоритма
    //researchTime(200000000);

    system("clear");

    system("cd");
    // исходный массив, отсортированная копия массива, буфер
    int *arr, *arr_sorted, *buf;
    // число элементов
    int N;

    // вводим входные данные
    inputData(arr, buf, arr_sorted, N);

    // вывод промежуточных данных, если число элементов <= 30
    bool output = (N <= 30);

    if (output)
    {
        cout << "\nArray: ";
        printArray(arr, 0, N - 1);
        cout << "\n\n";
    }

    // засекаем время начала сортировки
    auto start = std::chrono::high_resolution_clock::now();

    mergeSortIterative(arr, buf, N, output);

    // время конца сортировки
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    cout << "\nSorting finished in " << microseconds << " microseconds\n";

    if (output)
    {
        cout << "\nArray sorted with mergesort : [";
        printArray(arr, 0, N - 1);
        cout << "]\nArray sorted with std::sort : [";
        printArray(arr_sorted, 0, N - 1);
        cout << "]\n";
    }

    // проверяем корректность алгоритма
    if (memcmp(arr, arr_sorted, N) == 0)
    {
        cout << "Array was successfully sorted\n";
    }
    else
    {
        cerr << "Array wasn't sorted!\n";
    }

    // освобождаем память
    delete[] arr;
    delete[] arr_sorted;
    delete[] buf;

    return 0;
}


void inputData(int *&arr, int*& buf, int *&arr_sorted, int &N)
{
    int action;
    int elem;

    cout << "1) Input from console\n" <<
            "2) Input from file\n" <<
            "3) Fill with random numbers\n";
    do
    {
        cout << "--> ";
        cin >> action;
    } while ((action <= 0) || (action > 3));

    switch (action)
    {
        case 1:
        {
            cout << "Enter number of elements: ";
            cin >> N;

            if (N <= 0)
            {
                cerr << "Number of elements must be positive";
                exit(1);
            }

            arr = new int[N];
            buf = new int[N];

            cout << "Enter " << N << " integers: \n";

            for (int i = 0; i < N; i++)
            {
                cin >> elem;
                arr[i] = elem;
            }

            break;
        }

        case 2:
        {
            ifstream fin("input.txt");

            if (!fin.is_open())
            {
                cerr << "Unable to open input file\n";
                exit(1);
            }

            fin >> N;
            if (N <= 0)
            {
                cerr << "Number of elements must be positive";
                exit(1);
            }

            arr = new int[N];
            buf = new int[N];

            for (int i = 0; i < N; i++)
            {
                fin >> elem;
                arr[i] = elem;
            }

            fin.close();

            break;
        }

        case 3:
        {
            srand(time(NULL));

            cout << "Enter number of elements: ";
            cin >> N;

            if (N <= 0)
            {
                cerr << "Number of elements must be positive";
                exit(1);
            }

            arr = new int[N];
            buf = new int[N];

            for (int i = 0; i < N; i++)
            {
                arr[i] = rand() % (2*N) - N;
            }

            break;
        }

        default:
            cerr << "Unknown error";
            exit(1);
            break;
    }

    // выделяем память под копию массива
    arr_sorted = new int[N];
    // создаем копию массива для дальнейшей проверки корректности
    memcpy(arr_sorted, arr, N * sizeof(int));
    // сортируем стандартным алгоритмом сортировки
    std::sort(arr_sorted, arr_sorted + N);
}
