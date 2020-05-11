#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Don't forget that cs50.h isn't locally on the computer, you have to use the CS50 IDE to compile...

int main(){

    string length = get_string("Height: ");
    int len = atoi(length);

    while(len < 1 || len > 8 ){
        length = get_string("Height: ");
        len = atoi(length);
    }

    int acc;

    for(int i=0; i<len; i++){
        acc = len - i- 1;
        for(int x=0; x<acc; x++){
            printf(" ");
        }
        for(int x=0; x<(i+1); x++){
            printf("#");
        }

        printf("  ");

        for(int x=0; x<(i+1); x++){
            printf("#");
        }
        // for(int x=0; x<acc; x++){
        //     printf(" ");
        // }

        printf("\n");
    }

}