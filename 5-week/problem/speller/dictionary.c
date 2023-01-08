// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <cs50.h>

#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO 4
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO 2: Improve this hash function
    return toupper(word[0]) - 'A';
}

static FILE *get_file(const char *file_path);
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic_file = get_file(dictionary);

    char word[LENGTH + 1];

    while(fscanf(dic_file, "%s", word) != EOF)
    {
        printf("oi");
    }

    /**
    1) Load dictionary file
    2) Read strings from file one at a time
    3) Create a new node for each word
    4) 'hash word to obtain a hash value'?
    5) 'insert node into hash table at that location'
    2 Load in a hash table
    Hash Table. A B C
    "Will return if this is in 'A' linked list, or in 'B' link list"
     */

    // node *n = malloc(sizeof(node));
    // strcpy(n->word, "Hello");
    // n->next = NULL;

    return false;
}

/**
 * @brief Get File. Path passed by param, in argv
 * @param file_path Path of file to analyze
 * @return FILE* object
 */
static FILE *get_file(const char *file_path)
{
    FILE *dic_file = fopen(file_path, "r");
    if (dic_file == NULL)
    {
        printf("Could not open %s\n", file_path);
        exit(2);
    }
    return dic_file;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO 3
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO 5
    return false;
}
