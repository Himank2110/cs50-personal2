// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// variable to count no. of words
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 0, sum = 0;
    while (word[i] != '\0')
    {
        sum += (toupper(word[i]) - 'A') * (int) pow(26, i);
        i++;
        if (i == 3)
        {
            break; // Only checks the first 3 letters to get hash value
        }
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(d, "%s", word) != EOF) // Loop until end of file(EOF)
    {
        count++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory\n");
            return false;
        }
        strcpy(n->word, word); // Copies each word from dictionary to table in memory
        int i = hash(n->word);
        n->next = table[i];
        table[i] = n;
    }
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor, *tmp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
