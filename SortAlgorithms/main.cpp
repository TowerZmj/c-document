#include "sortAlgorithms.h"
#include <cstdio>

int main()
{
    int array[100];
    printf("Please input the array:\n");
    int num;
    int length=0;
    while(scanf("%d", &num) == 1){
        array[length++] = num;
    }
    int choose = 0;
    printf("Please input the choose for sort Algorithm\n");
    printf("1 for quick sort\n");
    printf("2 for insertion sort\n");
    scanf("%d", &choose);
    switch(choose){
        case 1:        
            quickSort(array, length);
            break;
        case 2:
            insertionSort(array, length);
            break;
    }
    printf("result:\n");
    printf("-------------------------------------------\n");
    for(int i=0; i<length; i++){
        printf("%d\n", array[i]);
    }
    printf("-------------------------------------------\n");
    return 0;
}
