#include <stdio.h>
#include <cs50.h>

int main(){
    long card = 0;
    while(card == 0){
        card = get_long("Number: ");
    }

    int arr[16];
    long div = 1e15;

    // Obtain each of ints to do...
    for( int i=0; i<16; i++){
        arr[i] = card/div;
        card -= arr[i]*div;
        div /= 10;

        // printf("arr[%d]: %d\n",i , arr[i]);
    }

    int sumOdd = 0;
    int sum = 0;

    for(int i=0; i<16; i++){
        if( i%2 ){
            sum += arr[i];
        } else {
            // Add the products' digits together...
            // JANKY
            switch(arr[i]){
                case 1:
                    sumOdd += 2;
                    break;
                case 2:
                    sumOdd += 4;
                    break;
                case 3:
                    sumOdd += 6;
                    break;
                case 4:
                    sumOdd += 8;
                    break;
                case 5:
                    sumOdd += 1;    // 1+0
                    break;
                case 6:
                    sumOdd += 3;    // 1+2
                    break;
                case 7:
                    sumOdd += 5;    // 1+4
                    break;
                case 8:
                    sumOdd += 7;    // 1+6
                    break;
                case 9:
                    sumOdd += 9;    // 1+9
                    break;
                default:
                    break;
                    // Includes 0
            }
        }
    }

    // printf("SumOdd: %d\n", sumOdd);

    sum += sumOdd;

    // printf("Sum: %d\n", sum);

    if( sum%10 == 0 ){
        // Check what kind of card it is:
        if(arr[0]==5 && (arr[1]==1 || arr[1]==2 || arr[1]==3 || arr[1]==4 || arr[1]==5) ){
            printf("MASTERCARD\n");
        } else if(arr[0]==0 && arr[1]==3 && (arr[2]==4 || arr[2]==7)){
            printf("AMEX\n");
        } else if(arr[0]==4 || (arr[0]==0 && arr[1]==0 && arr[2]==0 && arr[3]==4)){
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }


}