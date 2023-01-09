// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
    long int size;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int g_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *aux = table[hash(&word[0])];

    while (aux)
    {
        // 0 is equivalent
        if (strcasecmp(aux->word, word) == 0)
        {
            return (true);
        }
        aux = aux->next;
    }
    return (false);
    // return (table[hash(toupper(word))] == NULL);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Provavelmente terá q ser tratado 2 letras aqui
    return toupper(word[0]) - 'A';
}

static FILE *get_file(const char *file_path);
bool load(const char *dictionary)
{
    // Get the file
    FILE *dic_file = get_file(dictionary);
    if (dic_file == NULL)
    {
        return (false);
    }
    char word[LENGTH + 1];

    while(fscanf(dic_file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Allocate memory problem");
            // exit(3);
            return (false);
        }
        n->next = NULL;
        // strcpy(n->word, word);
        strncpy(n->word, word, strlen(word));
        // Get Hash Code
        unsigned int hash_code = hash(&word[0]);
        // Verify is this is the first register in hash table
        if (table[hash_code] == NULL)
        {
            // Just add node
            table[hash_code] = n;
        }
        else
        {
            // Add node in the begin.
            node *aux = malloc(sizeof(node));
            aux = table[hash_code];
            table[hash_code] = n;
            // Fixing the appointment
            n->next = aux;
        }
        g_count++;
    }
    return (true);
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
    return(g_count);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool result = false;
    for (int i = 'a'; i < 'z'; i++)
    {
        const char *c = (const char *)&i;
        if (check(c))
        {
            while (table[i])
            {
                node *temp = table[i];
                free(temp);
                table[i] = table[i]->next;
            }
            result = true;
        }
    }
    return (result);
}
