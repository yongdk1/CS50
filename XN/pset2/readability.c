#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main()
{
    string text;
    int letter = 0, word = 1, sentence = 0;
    int i;
    float index;

    text = get_string("Text: ");
// traverse the string to identify letters, words, and sentences via various features stated in the problem
    for (i = 0; i < strlen(text); i++){
        if(isalpha(text[i])){
            letter ++;
        }
        else if (text[i] == ' '){
            word ++;
        }
        else if (text[i] == '.'||text[i] == '?'||text[i] == '!'){
            sentence ++;
        }
    }
    /*printf("%d letter(s)\n", letter);
    printf("%d word(s)\n", word);
    printf("%d sentence(s)\n", sentence);
    */
    
    index = 0.0588 * ((float)letter/(float)word) * 100 - 0.296 * ((float)sentence/(float)word) * 100 - 15.8;
    //printf ("%f \n", index);
    if(index >= 1 && index < 16){
        printf("Grade %d\n", (int)round(index));
    }
    else if (index >= 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Before Grade 1\n");
    }
}
