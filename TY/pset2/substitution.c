#include <stdio.h>
#include <cs50.h>
#include <string.h>
// #include <math.h>

#define CIPHER_LEN 26

int isUpper(char c);
int isLower(char c);
int isAlpha(char c);
char toUpper(char c);   // Converts all to uppercase text
char toLower(char c);   // Converts to lowercase
int cipherComplete(char* cipher);   // Checks if the cipher does have 26 unique letters


int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("Please provide a cipher.\n");
        return 1;
    }
    char cipher[CIPHER_LEN];
    strcpy(cipher, argv[1]);

    if(!cipherComplete(cipher)){
        printf("Please provide unique letters for the cipher.\n");
        return 1;
    }

    char cipherLower[CIPHER_LEN];
    for(int i=0; i<CIPHER_LEN; i++){
        cipherLower[i] = toLower(cipher[i]);
        cipher[i] = toUpper(cipher[i]);
    }

    string plaintext = get_string("plaintext: ");

    char ciphertext[strlen(plaintext)];
    for(int i=0; i<strlen(plaintext); i++){
        char c = plaintext[i];
        if(isAlpha(c)){
            if(isUpper(c)){
                // Uppercase cipher
                ciphertext[i] = cipher[c-65];
            } else {
                // Lowercase cipher
                ciphertext[i] = cipherLower[c-97];
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n", ciphertext);    

    return 0;
}

int isUpper(char c){
    if(c>64 && c<91)
        return 1;
    return 0;
}
int isLower(char c){
    if(c>96 && c<123)
        return 1;
    return 0;
}
int isAlpha(char c){
    if(isLower(c) || isUpper(c))
        return 1;
    return 0;
}
char toUpper(char c){
    if(isLower(c)){
        return c-32;
    } else {
        return c;   // Don't modify c if it is not an alphabet.
    }
}
char toLower(char c){
    if(isUpper(c)){
        return c+32;
    } else {
        return c;
    }
}
int cipherComplete(char* cipher){
    // Init 0-initialized array that keeps track of a cipher.
    int track[CIPHER_LEN] = {0};

    // Update tracking array
    for(int i=0; i<CIPHER_LEN; i++){
        char c = toUpper(cipher[i]);
        track[(int)c-65]++;
    }
    // Check tracking array
    for(int i=0; i<CIPHER_LEN; i++){
        if(track[i]!=1){
            return 0;
        }
    }
    return 1;
}