#include <stdio.h>

void bigIntFactorial(const int facNum);

int main()
{
    printf("Please input the number:");
    int facNum;
    scanf("%d", &facNum);

    bigIntFactorial(facNum);
    return 0;
}

void bigIntFactorial(const int facNum)
{
    int bigInt[3000];

    int carry;
    int digits = 1;
    
    bigInt[0] = 1;
    int i, j;
    int temp;
    for(i=2; i<=facNum; i++){
        carry = 0;
        for(j=0; j<digits; j++){
            temp = bigInt[j] * i + carry;
            bigInt[j] = temp % 10;
            carry = temp / 10;          
            
        }
        while(carry){
            bigInt[digits] = carry % 10;
            carry = carry / 10;
            digits++;
        }
    }
    
    for(i=digits-1; i>=0; i--){
        printf("%d", bigInt[i]);
    }
    printf("\n");
}

