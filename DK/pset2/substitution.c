#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//https://cs50.harvard.edu/x/2020/psets/2/substitution/

int main(int argc, string argv[])
{
    //case where function has more inputs than expected (1)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //case where input is not the expected length (26)
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 letters\n");
        return 1;
    }

    string text = argv[1];
    char alphabet[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char key[52];

    for (int i = 0; i < 26; i++)
    {
        // printf("%c\n", text[i]);
        char itemi = text[i];
        itemi = tolower(itemi);
        //case where input has non-alphabetic characters
        if ((text[i] > 'Z' && text[i] < 'a') || text[i] < 'A' || text[i] > 'z')
        {
            printf("Key must only contain letters\n");
            return 1;
        }
        //case where input has repeated alphabetic characters
        for (int j = 0; j < 26; j++)
        {
            char itemj = text[j];
            itemj = tolower(itemj);
            if (itemi == itemj && i != j)
            {
                printf("Key must not contain repeated letters\n");
                return 1;
            }
            key[i] = itemi;
            key[i + 26] = toupper(itemi);
        }
    }

    printf("%s\n", key);

    //get user input string
    string input = get_string("plaintext: ");
    int length = strlen(input);

    //convert input string to ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        //case where character is not a letter and reprints them
        if ((input[i] > 'Z' && input[i] < 'a') || input[i] < 'A' || input[i] > 'z')
        {
            printf("%c", input[i]);
        }
        //case where character is a letter and converts them to cipher letter
        else
        {
            for (int j = 0; j < 52; j++)
            {
                if (input[i] == alphabet[j])
                {
                    printf("%c", key[j]);
                    break;
                }
            }
        }
    }
    printf("\n");

}
