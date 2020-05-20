#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    int i,j;
    char key[52];
    
    const char* cipher(string plain, string key);
    
    //check if user inputs a key in the command line
    if(argc != 2){
        printf("Please input key!\n");
        return 1;
    }
    else if(argc == 2){
        //check if key input is 26 characters
        if(strlen(argv[1]) != 26){
            printf("Key must contain 26 letters!\n");
            return 1;
        }
        else{
            for(i = 0; i < 26; i++){
                //check for non-alphabets
                if(isalpha(argv[1][i]) == 0){
                    printf("Please ensure key contains only alphabetic characters!\n");
                    return 1;
                }
                //check for repeated alphabets
                for(j = i + 1; j < 26 - i; j++){
                    if(toupper(argv[1][i]) == toupper(argv[1][j])){
                        printf("Please ensure characters in key are not repeated!\n");
                        return 1;
                    }
                }
            }
        }
    }
    //printf("%s\n", argv[1]);
    for(i =  0; i < 26; i++){
        key[i] = (char)toupper(argv[1][i]);
    }
    for (i = 26; i < 52; i++){
        key[i] = (char)tolower(argv[1][i-26]);
    }
    //printf("%s\n", key);

    
    string plaintext;
    
    plaintext = get_string("plaintext: ");
    printf("ciphertext: %s \n", cipher(plaintext, key));
}

const char* cipher(string plain, string key){
    int i;
    int n = strlen(plain);
    char ciphertext[n];
    for(i = 0; i < n; i++){
        if(isalpha(plain[i])){
            //cipher alphabets
            if(isupper(plain[i])){
                ciphertext[i] = key[plain[i]-65];
            }
            else{
                ciphertext[i] = key[plain[i]-71];
            }
        }
        else{
            //no change for non-alphbets
            ciphertext[i] = plain[i];
        }
    }
    char *ctext = ciphertext;
    return ctext;
}
