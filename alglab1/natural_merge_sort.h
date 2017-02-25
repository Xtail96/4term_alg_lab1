#ifndef NATURAL_MERGE_SORT_H
#define NATURAL_MERGE_SORT_H
#include <vector>

// максимальная глубина рекурсивного вызова
const int RECURSION_LIMIT = 1024;
/**
  * Сортирует массив, используя итеративную сортировку слиянием
  * arr - указатель на массив, который нужно сортировать
  * buf - буферный массив размера не менее, чем 'arr'
  * size - размер массива
  * output - выводить ли промежуточные данные
  *
  **/
void mergeSortIterative(int *arr, int *buf, int size, bool output);

// Слияние упорядоченных частей массива
void merge(int *arr, int *buf, int left, int middle, int right);


void printArray(int *arr, int begin, int end);


#endif // NATURAL_MERGE_SORT_H
