#include <stdio.h>
#include <cs50.h>

//https://cs50.harvard.edu/x/2020/psets/1/mario/more/

int main(void)
{
    int input;
    //take user input of how tall they want the pyramid to be
    do
    {
        input = get_int("Height: ");
    }
    //ask for user input until they give an integer between 1 and 8 inclusive
    while ((input < 1 || input > 8));
    //iterate through each row of the pyramid
    for (int i = 1; i <= input; i++)
    {
        //print whitespace
        for (int j = 0; j < (input - i); j++)
        {
            printf(" ");
        }
        //print #
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        //print double whitespace
        printf("  ");
        //print # mirrored
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        //create newline for next row of pyramid
        printf("\n");
    }
}
