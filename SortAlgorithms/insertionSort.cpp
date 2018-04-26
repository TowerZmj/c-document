#include "sortAlgorithms.h"

void insertionSort(int num[], int length)
{
    for(int j=1; j<length; j++){
        int key = num[j];
        int i = j - 1;
        while((i >= 0) && (num[i] > key)){
            num[i+1] = num[i];
            i--;
        }
        num[i+1] = key;
    }
}
