#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int* getParameters(string x);   // Returns as an int array.
int isAlpha(char c);
int isPunct(char c);

int main(){
    string text = get_string("Text: ");
    int* params;
    params = getParameters(text);

    // printf("%d letter(s)\n", params[0]);
    // printf("%d word(s)\n", params[1]);
    // printf("%d sentence(s)\n", params[2]);

    float L = (float)params[0]/(float)params[1]*100.0f;  //L is the average number of letters per 100 words in the text
    float S = (float)params[2]/(float)params[1]*100.0f;  //S is the average number of sentences per 100 words in the text.

    float index = (0.0588*L) - (0.296*S) - 15.8;

    int grade = round(index);

    if(grade>16)
        printf("Grade 16+\n");
    else if(grade<1)
        printf("Before Grade 1\n");
    else
        printf("Grade %d\n", grade);

}

int* getParameters(string x){
    static int r[3] = {0,1,0};

    for(int i=0; i<strlen(x); i++){
        if(isAlpha(x[i]))
            r[0]++;

        if(x[i]==' ')
            r[1]++;

        if(isPunct(x[i]))
            r[2]++;
    }

    return r;
}

int isAlpha(char c){
    if( (c>64 && c<91) || (c>96 && c<123) )
        return 1;
    return 0;
}

int isPunct(char c){
    if( c=='.' || c=='?' || c=='!' )
        return 1;
    return 0;
}