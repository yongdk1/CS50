#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//https://cs50.harvard.edu/x/2020/psets/2/readability/

int main(void)
{
    //get user input text as string
    string text = get_string("Text: ");
    //determine length of input text
    int length = strlen(text);
    float letterCount = 0;
    float wordCount = 1;
    float sentenceCount = 0;

    //iterate over input string to determine letterCount, wordCount and sentenceCount
    for (int i = 0; i < length; i++)
    {
        if ((text[i] <= 'z' && text[i] >= 'a') || (text[i] <= 'Z' && text[i] >= 'A'))
        {
            letterCount ++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentenceCount ++;
        }
        else if (text[i] == ' ')
        {
            wordCount ++;
        }
    }

    //determine average number of letters per 100 words
    float L = letterCount / wordCount * 100;

    //determine average number of sentences per 100 words
    float S = sentenceCount / wordCount * 100;

    //calculate coleman-liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    /*
    printf("%d letters\n", (int) letterCount);
    printf("%d words\n", (int) wordCount);
    printf("%d sentences\n", (int) sentenceCount);
    printf("%f\n", index);
    */

    //print grade
    if (grade >= 1 && grade <= 16)
    {
        printf("Grade %d\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
}
