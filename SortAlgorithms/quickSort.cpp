#include "sortAlgorithms.h"

void quickSort(int num[], int length)
{
    if((length == 0) || (length == 1))
        return;
    
    int index = length -1;
    int i;
    int j = 0;
    int temp;
    for(i=0; i<length-1; i++){
        if(num[i] < num[index]){
            temp = num[i];
            num[i] = num[j];
            num[j] = temp;
            j++;
        }
    }
    temp = num[index];
    num[index] = num[j];
    num[j] = temp;
    
    quickSort(num, j);
    quickSort(num+j+1, length-j-1);
}
