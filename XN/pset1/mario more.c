#include <stdio.h>
#include <cs50.h>

int main()
{
    int h,i,j,k;
    
    do{
        h = get_int("Height:");
    }
    while (h<1 || h>8);
    // ensure input is valid
    for (i=1; i<h+1; i++){
    //counting of rows
        for (k=h-i;k>0;k--){
            printf(" ");
        }
        //padding of spaces
        for (j=0;j<i;j++){
            printf("#");
        }
        
        printf(" ");
        printf(" ");
        
        for (j=0;j<i;j++){
            printf("#");
        }
        //printing of hashes and spacings
    printf("\n");
    //moving to next row
    }
}
