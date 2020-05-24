#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    int i,j;
    char key[52];
    
    char *cipher(string plain, string key);
    
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
    //creating an array to sore the key, [0]-[25] stores the uppercase and [26]-[51] stores lowercase
    for(i =  0; i < 26; i++){
        key[i] = (char)toupper(argv[1][i]);
    }
    for (i = 26; i < 52; i++){
        key[i] = (char)tolower(argv[1][i-26]);
    }

    
    string plaintext;
    
    plaintext = get_string("plaintext: ");
    printf("ciphertext: %s\n", cipher(plaintext, key));
}

//as string in C is an array of char, the function cannot return the entire string directly,
//so we have to make it return a pointer that points to the start of the string
char *cipher(string plain, string key){
    int i;
    //variable n that depends on the length of user input
    int n = strlen(plain);
    char ciphertext[n]; 
    //important to note here that we need to iterate till i < n+1 to copy the '\0' char
    for(i = 0; i < n+1; i++){
        if(isalpha(plain[i])){
            //cipher alphabets
            if(isupper(plain[i])){
                //converting plaintext to ciphertext through arithmetic operation on ASCII 
                //code to produce corresponding index in the key array
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
    //pointer to point to the address of the first char of ciphertext
    char *ctext = ciphertext;
    //returns the address stored in the pointer
    return ctext;
}
