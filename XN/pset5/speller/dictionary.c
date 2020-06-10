// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// File for dictionary
FILE *dict;

// Number of words in the diectionary
int word_count;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initialize a temp node to traverse the linked list
    node *temp;
    // Copy of the word
    char copy[strlen(word) + 1];

    // Conver the copy to lowercase (need to convert to get the correct hash!!!)
    for (int i = 0; i < strlen(word); i++){
       copy[i] = tolower(word[i]);
    }

    // Ensure terminating char for copy
    copy[strlen(word)] = '\0';

    // temp will point to the start of the linked list stored in the coresponding hash table index
    temp = table[hash(copy)];

    // Loop through the linked list
    while (temp != NULL){
        // If the word in a particular node is the same as the word, the word exist in the dictionary
        if (strcasecmp(temp->word, word) == 0){
            return true;
        }
        // Else traverse to the next node
        temp = temp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash_index;

    // To handle 1-char words!!!
    if (strlen(word) > 1){
        // Find the index of the hash table which the word belongs to, using the first 2 characters
        hash_index = ((int)word[0] - 97) * 26 + (word[1] - 97);
    }
    else {
        hash_index = ((int)word[0] - 97) * 26;
    }

    return hash_index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // String to store the word nd make sure it is initialized!!!
    char *word = malloc(sizeof(char) * (LENGTH + 1));

    //To store the hash table index of the word
    int hash_idx;

    // Open the file and store it as dict
    dict = fopen(dictionary, "r");

    // Initialize word count
    word_count = 0;

    if (dict == NULL){
        // If file could not be opened, return false
        return false;
    }
    //Read the file string by string until the end
    while (fscanf(dict, "%s", word) != EOF){
        // Create a new node for the word
        node *n = malloc(sizeof(node));

        // If no memory, return false
        if (n == NULL){
            return false;
        }

        // Copy the word into the node
        strcpy(n->word, word);

        // Find which index of the hash table the word belongs in
        hash_idx = hash(word);

        // If there is not linked list at the index
        if (table[hash_idx] == NULL){

            // The space in the table will store the pointer to the new node
            table[hash_idx] = n;
            // The n-> should not point at anything
            n->next = NULL;
        }
        // Append the node to the start of the list
        else{
            // The n->next will point to the start of the linked list
            n->next = table[hash_idx];
            //The table will now store the pointer to the node
            table[hash_idx] = n;
        }

        // Increase count of words
        word_count++;
    }
    // Free word!!!
    free(word);

    // Close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Initiate cursor and temp
    node *cursor;
    node *temp;

    // Iterate through the hash table
    for (int i = 0; i < N; i ++){
        // Cursor will point to the start of the linked list
        cursor = table[i];

        //Go throught the linked list until the cursor reaches the end
        while (cursor != NULL){
            // Temp will start by pointing to the same place as the cursor
            temp =  cursor;
            // Cursor will point to the next node
            cursor = cursor->next;
            // Free temp
            free(temp);
        }
    }
    return true;
}
