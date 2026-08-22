// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
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
        if (i == 3){break;}
    }
    return sum % N;
}
/*     if (word[1] != '\0')
    {
        return ((toupper(word[0]) - 'A') * 26) +  toupper(word[1]) - 'A';
    }
    else
    {
        return ((toupper(word[0]) - 'A') * 26);
    }
*/
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
    while(fscanf(d, "%s", word) != EOF)
    {
        count++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory\n");
            return false;
        }
        strcpy(n->word, word);
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
