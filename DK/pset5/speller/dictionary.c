// https://cs50.harvard.edu/x/2020/psets/5/speller/

// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Initialise variable to store size of dictionary
int wordCount = 0;

// Number of buckets in hash table
const unsigned int N = 269;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Using a variation of djib2, k=33 developed by dan bernstein
    unsigned int key = 5381;
    for (int i = 0; i < strlen(word); i++)
    {
        int letter = tolower(word[i]);
        key = ((key << 5) + key) + letter; /* hash * 33 + letter */
    }
    key = key % 269;
    return key;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Initialise variables word to store current word and wordCount
    char word[LENGTH + 1];

    // Read strings from files one at a time
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));

        // Initialise n->next to ensure that unloading isnt performed on an uninitialised value by valgrind
        n->next = NULL;

        // Case where not enough memory to initialise n
        if (n == NULL)
        {
            return false;
        }

        // Copy word to node->word
        strcpy(n->word, word);

        // Hash word to find a hash value
        int hashValue = hash(word);

        // Insert node into hash table at that location
        // Case where it is first node of that hashed list
        if (table[hashValue] == NULL)
        {
            table[hashValue] = n;
        }
        // All other cases
        else
        {
            n->next = table[hashValue];
            table[hashValue] = n;
        }

        // Increment wordCount
        wordCount ++;

    }

    // Close dictionary
    fclose(dict);

    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // Hash word to find hash value
    int hashValue = hash(word);

    // Check hashtable from index of hashValue
    // Case where hashed list does not have that node
    if (table[hashValue] == NULL)
    {
        return false;
    }
    // All other cases
    else
    {
        // Initialise pointer to current node being compared with
        node *cursor = table[hashValue];
        // Iterate through linked list
        while (cursor != NULL)
        {
            // Check if word is in the current node
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            // Set cursor to next node
            else
            {
                cursor = cursor->next;
            }
        }
    }

    // Return false when no words have matched
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // Initialize cursor and tmp node pointers
    node *cursor = NULL;
    node *tmp = NULL;

    // Iterate through hash table
    for (int i = 0; i < N; i++)
    {
        // Check if hash table index if not empty
        if (table[i] != NULL)
        {
            // Assign tmp to table pointer
            tmp = table[i];
            // Iterate through linked list
            while (tmp != NULL)
            {
                // Assign cursor to node after tmp, free tmp, then assign tmp to cursor and repeat until all freed
                cursor = tmp->next;
                free(tmp);
                tmp = cursor;
            }
        }
    }

    // Free cursor and tmp pointers
    free(cursor);
    free(tmp);

    return true;
}
