#include <stdio.h>
#include <cs50.h>
#include <math.h>

//https://cs50.harvard.edu/x/2020/psets/1/credit/

int main(void)
{
    //request for input credit card number
    long creditNum = get_long("Number: ");

    // count number of digits
    int numLength = 0;
    long n = creditNum;
    while (n != 0)
    {
        n /= 10;
        numLength++;
    }

    //check if input credit card number is an appropriate length
    if (numLength == 13 || numLength == 15 || numLength == 16)
    {
        int numberArray[numLength];
        int c = numLength;
        n = creditNum;

        // extract each digit and place into an array
        while (n != 0)
        {
            numberArray[c - 1] = n % 10;
            n /= 10;
            c--;
        }

        int numTotal = 0;
        //run luhn's algorithm on the input number
        for (int i = (numLength - 2); i >= 0; i -= 2)
        {
            if (numberArray[i] < 5)
            {
                numTotal += numberArray[i] * 2;
            }
            if (numberArray[i] >= 5)
            {
                numTotal += (numberArray[i] - 4) * 2 - 1;
            }
        }

        for (int i = (numLength - 1); i >= 0; i -= 2)
        {
            numTotal += numberArray[i];
        }

        //check if luhn's algorithm is true for the input number
        if (numTotal % 10 == 0)
        {
            //case for AMEX
            if (numLength == 15 && numberArray[0] == 3 && (numberArray[1] == 4 || numberArray[1] == 7))
            {
                printf("AMEX\n");
            }
            //case for MASTERCARD
            else if (numLength == 16 && numberArray[0] == 5 && (numberArray[1] == 1 || numberArray[1] == 2 || numberArray[1] == 3 ||
                     numberArray[1] == 4 || numberArray[1] == 5))
            {
                printf("MASTERCARD\n");
            }
            //case for VISA
            else if ((numLength == 13 || numLength == 16) && numberArray[0] == 4)
            {
                printf("VISA\n");
            }
            //case if none are valid
            else
            {
                printf("INVALID\n");
            }
        }
        //case if luhn's algorithm is not true
        else
        {
            printf("INVALID\n");
        }
    }
    //case if length of input string is not valid (13, 15 or 16)
    else
    {
        printf("INVALID\n");
    }
}
